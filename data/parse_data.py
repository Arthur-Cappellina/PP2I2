import json 

# Open stations.json
with open('data/stations.json', 'r') as f:
    f = json.load(f)

def check_lat_lont(station, lat, lont):
    for s in station:
        if s["lat"] == lat and s["lont"] == lont:
            return True

# Create a list of stations
stations = []
for i in f["features"]:
    try:
        if i["properties"]["nom_station"][0] == " " or i["properties"]["nom_station"][0] == "	": 
            name = i["properties"]["nom_station"][1:]
        else:
            name = i["properties"]["nom_station"]
        station = {
            "address": i["properties"]["adresse_station"].replace(",", "").replace("\n", " "),
            "name": name.replace(",", "").replace("\n", " "),
            "lat": i["geometry"]["coordinates"][1],
            "lon": i["geometry"]["coordinates"][0],
            "station_deux_roues": i["properties"]["station_deux_roues"],
            "nbre_pdc": i["properties"]["nbre_pdc"],
            "puissance_nominale": i["properties"]["puissance_nominale"]
        }
        if station not in stations and not check_lat_lont(stations, station["lat"], station["lon"]):
            stations.append(station)
    except Exception as e: 
        pass



stations_sorted = sorted(stations, key=lambda x: x['name'])

# save the list of stations in a csv file
with open('data/stations.csv', 'w', encoding="utf-8") as f:
    f.write("id,name,address,lat,lon,station_deux_roues,nbre_pdc,puissance_nominale\n")
    i = 0
    for s in stations_sorted:
        f.write("%i, %s,%s,%s,%s,%s,%s,%s\n"%(i,s["name"], s["address"], s["lat"], s["lon"], s["station_deux_roues"], s["nbre_pdc"], s["puissance_nominale"]))
        i += 1