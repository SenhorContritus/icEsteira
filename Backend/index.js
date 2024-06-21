const express = require("express");
const server = express();
const cors = require("cors")
const bodyParser = require("body-parser");
const mqtt = require("mqtt");
const mtqqURL = "mtqq://broker.hivemq.com";
const clientID = `mqtt_${Math.random().toString(16).slice(3)}`;
process.setMaxListeners(0);


require('events').EventEmitter.defaultMaxListeners = 0;
const client = mqtt.connect(mtqqURL,{
    clientID,
    clean: true,
    connectTimeout: 4000,
    username: 'server',
    password: 'public',
    reconnectPeriod: 1000   
});

client.on('connect', () =>{
    console.log("Conectado ao servidor mqtt");
    
    client.subscribe('/esteira/receber/', () =>{
        console.log("subscribed on /esteira/receber/");

    });

})
client.on("message" ,( topic , payload)  =>{
    console.log("mensagem:", payload.toString());
});

module.exports = client;

exports.handler = async (event) =>{
    const response = {
        statusCode:200,
        Headers:{
        "Access-Control-Allow-Headers" : "Content-Type",
        "Access-Control-Allow-Origin": "*",
        "Access-Control-Allow-Methods": "OPTIONS,POST,GET"
        }
    }

    return response;
}
server.use(cors())
server.use(bodyParser.json())

require("./Controller/getController")(server);

server.listen("8081" , () =>{
    console.log("Server is running on port 8081! ");
});