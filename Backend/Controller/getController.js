const express = require("express");
const router = express.Router();
const ID = "admin";
const PASS = "admin";
const client = require("../index.js");
process.setMaxListeners(0);
require('events').EventEmitter.defaultMaxListeners = 0;

router.get("/mqtt", async (req, res) =>{

    
    client.on("message" ,( topic , payload)  =>{
        try {
            res.status(200).json({valor : payload.toString()});
        } catch (error) {
            
        }
    });

});

router.get("/get", async (req,res) => {

    res.send("SERVER:ONLINE");
    console.log("Conexão estabelecida com o front");

})

router.post("/post", async (req, res) =>{
    const response = await req.body;
    var id = response.id;
    var password = response.password;

    if(id === ID){
        if(password === PASS){
            res.send("User login OK");         

        }else{
            res.send("Password is incorrect!");
        }

    }else{
        res.send("Incorrect ID!");
    }


});



module.exports = (server) => server.use("/methods", router)