const APPID = "ChiApp";
const KEY = "W5wwspwT9N24OaT";
const SECRET = "OzA6mqIqwsH2uPjd2tZgNebuq";

const ALIAS = "pieled";

var microgear = Microgear.create({
    key: KEY,
    secret: SECRET,
    alias: ALIAS
});

let state = 0;

function toggle() {
    // var element = document.body;
    // element.classList.toggle("dark-mode");

    if (state === 1) {
        microgear.chat('pieled', '1');
        state = 0;
    } else {
        microgear.chat('pieled', '0');
        state = 1;
    }
}

microgear.on('message', function(topic, msg) {
    if (msg == "0") {
        // document.getElementById("button").innerText="";
        document.getElementById("data").innerHTML = "bulb is turn on";
    } else if (msg == "1") {
        // document.getElementById("button").innerText="";
        document.getElementById("data").innerHTML = "bulb is turn off";
    }
});

microgear.on('connected', function() {
    microgear.setAlias(ALIAS);
    document.getElementById("data").innerHTML = "Now I am connected with netpie...";
});

microgear.connect(APPID);