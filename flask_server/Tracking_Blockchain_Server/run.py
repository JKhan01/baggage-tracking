from flask import redirect,render_template,request, session
from flask import Flask
# import requests

app = Flask(__name__)
app.config['SECRET_KEY'] = "15de2e5584da6716f650e3d50fa752cd"

@app.route("/api/<baggage_id>/<checkpoint_no>")
def api_post(baggage_id,checkpoint_no):
    passenger_id = "p001"
    session[passenger_id] = {"hello":0}
    session["p001"][baggage_id] = checkpoint_no
    print (f"Baggage Number: {baggage_id} at checkpoint: {checkpoint_no}")
    return ("OK")

@app.route("/admin/enterpassenger",methods=["GET"])
def enter_passenger():
    new_passenger = str(request.args.get("pnr"))
    baggage_count = int(request.args.get("baggage_count"))
    baggage_ids = []
    for i in range(baggage_count):
        baggage_ids.append(str(request.args.get(f"b{i}")))

    session[new_passenger] = {}
    for j in baggage_ids:
        session[new_passenger][j] = 0


if __name__ == "__main__":
    app.run(host="0.0.0.0",port=5000,debug=True)
    