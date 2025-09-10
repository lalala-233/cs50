import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide symbol")
        if not shares:
            return apology("must provide shares")

        result = lookup(symbol)
        if not result:
            return apology("do not found this symbol")

        try:
            shares = int(shares)
        except ValueError:
            return apology("must provide positive integer")

        if shares <= 0:
            return apology("must provide positive integer")

        price = result["price"]
        user = db.execute("SELECT * FROM users WHERE id = ?", session.get("user_id"))[0]
        id = user["id"]
        total_price = shares * price

        new_cash = user["cash"] - total_price
        if new_cash < 0:
            return apology("do not have enough money")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, id)
            # This code may cause race conditions
            try:
                db.execute(
                    "INSERT INTO holdings (user_id, stock_symbol, shares) VALUES(?, ?, ?)",
                    id,
                    symbol,
                    shares,
                )
            # may db.IntegrityError
            except ValueError:
                db.execute(
                    "UPDATE holdings SET shares = shares + ? WHERE user_id = ? AND stock_symbol = ?",
                    shares,
                    id,
                    symbol,
                )
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        password = request.form.get("password")
        username = request.form.get("username")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
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
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol")
        else:
            return render_template("quoted.html", stock=lookup(symbol))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        password = request.form.get("password")
        username = request.form.get("username")
        confirmation = request.form.get("confirmation")
        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)
        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 403)
        elif not confirmation:
            return apology("must provide confirmation")

        if password != confirmation:
            return apology("password and confirmation do not match")

        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)",
                username,
                generate_password_hash(password),
            )
        except:
            return apology("user already exists", 409)

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session.get("user_id")
    if request.method == "GET":
        symbols = db.execute("SELECT stock_symbol FROM holdings WHERE user_id = ? AND shares != 0", id)
        return render_template("sell.html", symbols=symbols)
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol that you own")

        try:
            shares = int(shares)
        except ValueError:
            return apology("must provide positive integer")

        if not shares:
            return apology("must provide positive integer")

        holding = db.execute(
            "SELECT shares FROM holdings WHERE user_id = ? AND stock_symbol = ?",
            id,
            symbol,
        )

        if len(holding) != 1:
            return apology("must provide symbol that you own")

        holding = holding[0]["shares"]
        new_holding = holding - shares
        if new_holding < 0:
            return apology("do not own that many shares")
        else:
            price = lookup(symbol)["price"]
            db.execute(
                "UPDATE holdings SET shares = ? WHERE user_id = ? AND stock_symbol = ?",
                new_holding,
                id,
                symbol,
            )
            db.execute(
                "UPDATE users SET cash = cash + ? WHERE id = ?", shares * price, id
            )
            return redirect("/")
