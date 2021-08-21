import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    total = db.execute(
        "SELECT symbol, name, SUM(shares) AS shares,price, price*SUM(shares) AS total FROM transactions GROUP BY name HAVING person_id = ?;", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])

    return render_template("index.html", values=total, cash=cash)
    

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    # Check for error
    if request.method == "GET":
        return render_template("buy.html")
    if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
        return apology("Symbol invalid")
    elif isinstance(request.form.get("shares"), int):
        return apology("Invalid shares")
        
    try:
        float(request.form.get('shares'))
    except ValueError:
        return apology("Invalid shares")
        
    value = float(request.form.get('shares'))
    if value < 0:
        return apology("Negative")
    value = value - int(value)
    if value != 0:
        return apology("float")
    
    # Get form company and quantity
    company = lookup(request.form.get("symbol"))
    quantity = int(float(request.form.get('shares')))

    # Get current cash from user
    value = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
    money = value[0]["cash"] - company["price"] * quantity
    if company["price"] * quantity > value[0]["cash"]:
        return apology("Can't afford")

    # Get now time
    now = datetime.now()
    now = now.strftime("%d-%m-%Y %H:%M:%S")
    current = db.execute("SELECT shares FROM transactions WHERE person_id = ? AND symbol = ?", 
                         session['user_id'], company['symbol'])

    # If user already have a shares from this company, update the value, if not, create new table
    if not current:
        db.execute("INSERT INTO transactions VALUES (?,?,?,?,?)", 
                   session["user_id"], company["symbol"], company["name"], quantity, company["price"] * quantity)
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", money, session["user_id"])
        db.execute("INSERT INTO history VALUES (?,?,?,?,?)", session['user_id'], company['symbol'], quantity, company['price'], now)
    else:
        current = current[0]['shares']
        quantity = quantity + current
        db.execute("UPDATE transactions SET shares = ? WHERE person_id = ? AND symbol = ?;", 
                   quantity, session["user_id"], company['symbol'])
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", money, session["user_id"])
        db.execute("INSERT INTO history VALUES (?,?,?,?,?)", session['user_id'], company['symbol'], quantity, company['price'], now)

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get history from the database and send to HTML
    user = db.execute("SELECT * FROM history WHERE person_id = ?", session['user_id'])
    return render_template("history.html", values=user)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    
    # generate the code based in lookup
    quoted = lookup(request.form.get("symbol"))
    if not quoted:
        return apology("Invalid symbol")

    return render_template("quoted.html", value=quoted)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # If get return the register page, otherwise, insert the user in the database
    if request.method == "GET":
        return render_template("register.html")

    # Check for error
    if not request.form.get("username") or not request.form.get("password"):
        return apology("Username or password in blank")
    elif (request.form.get("password") != request.form.get("confirmation")):
        return apology("Both password must be the same")
    
    # Check if username already in use
    row = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
    if row:
        return apology("Username already in use", 400)

    # Insert user data in the database
    db.execute("INSERT INTO users (username, hash) VALUES (?,?)", request.form.get("username"),
               generate_password_hash(request.form.get("password")))
    
    return redirect("/")
    

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    total = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions GROUP BY name HAVING person_id = ?;", session["user_id"])

    # Check for errors
    if request.method == "GET":
        return render_template("sell.html", total=total)

    if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
        return apology("Symbol invalid")
    elif isinstance(request.form.get("shares"), int):
        return apology("Invalid shares")
        
    try:
        float(request.form.get('shares'))
    except ValueError:
        return apology("Invalid shares")
        
    value = float(request.form.get('shares'))
    if value < 0:
        return apology("Number must not be ")
    value = value - int(value)
    if value != 0:
        return apology("float")

    # Get quantity to be sold
    quantity = int(request.form.get("shares"))

    # Get current cash from user and convert to integer
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]['cash']

    # Get current shares that user have and convert from list to integer
    shares = db.execute("SELECT SUM(shares) AS shares FROM transactions GROUP BY name HAVING person_id = ? AND symbol = ?", 
                        session['user_id'], request.form.get("symbol"))
    shares = shares[0]['shares']

    # Check if the user is trying to sell a quantity that are bigger then it have
    if quantity > shares:
        return apology("The quantity is bigger then what you have")
        
    # Check for current price and convert to float
    company = lookup(request.form.get("symbol"))

    # Get now time
    now = datetime.now()
    now = now.strftime("%d-%m-%Y %H:%M:%S")

    # If quantity to be sold is equal to quantity that user have, delete from the table, if not, uptade the quantity value
    if quantity == shares:
        cash += company['price'] * quantity
        quantity = 0 - quantity
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session['user_id'])
        db.execute("DELETE FROM transactions WHERE person_id = ? AND symbol = ?", session["user_id"], request.form.get('symbol'))
        db.execute("INSERT INTO history VALUES (?,?,?,?,?)", session['user_id'], company['symbol'], quantity, company['price'], now)
    else:
        cash += company['price'] * quantity
        shares = shares - quantity
        price = company['price'] * shares
        quantity = 0 - quantity
        db.execute("UPDATE transactions SET shares = ? WHERE symbol = ? AND person_id = ?", 
                   shares, request.form.get('symbol'), session['user_id'])
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session['user_id'])
        db.execute("UPDATE transactions SET price = ? WHERE person_id = ? AND symbol = ?", 
                   price, session['user_id'], company['symbol'])
        db.execute("INSERT INTO history VALUES (?,?,?,?,?)", session['user_id'], company['symbol'], quantity, company['price'], now)

    return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
