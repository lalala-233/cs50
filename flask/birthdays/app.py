import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        form = request.form
        name = form["name"]
        month = form["month"]
        day = form["day"]
        if name and month and day:
            try:
                # TODO: Add the user's entry into the database
                month = int(month)
                day = int(day)
                if (
                    (month in [1, 3, 5, 7, 8, 10, 12] and day in range(1, 31 + 1))
                    or (month in [4, 6, 9, 12] and day in range(1, 30 + 1))
                    or (month == 2 and day in range(1, 29 + 1))
                ):
                    db.execute(
                        "INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)",
                        name,
                        month,
                        day,
                    )
            except ValueError:
                pass
        return redirect("/")
    else:
        # TODO: Display the entries in the database on index.html

        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)
