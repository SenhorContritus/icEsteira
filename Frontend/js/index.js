const p = document.getElementById("s-stats");
const inputId = document.getElementById("id");
const inputPass = document.getElementById("password");
const listQnt  =  document.getElementById("qnt-objetos");
const listVerm = document.getElementById("qnt-vermelho");
const listAzul = document.getElementById("qnt-azul");
const listVerd = document.getElementById("qnt-verde");
const listTempo = document.getElementById("tempo-dec");
const lista = document.getElementById("lista");
const buttonLogin = document.getElementById("btLogin");

var azul =0;
var vermelho = 0;
var verde =0;
var total = 0;

const url = "http://localhost:8081";

function submit(){
    let id = inputId.value;
    let pass = inputPass.value;
    console.log(pass);


    axios({
        method: "post",
        url: url+"/methods/post",
        data:{
            id:id,
            password: pass
        }
    }).then(async(response) =>{
        console.log(response);
        var isLogged = true;
        lista.style.display = "block";
        inputId.style.display = "none";
        inputPass.style.display = "none";
        buttonLogin.style.display = "none";
    });
    
}

axios({
    method: "get",
    url: url+"/methods/get"
}).then((response) => {
    console.log(response.data);
    p.innerHTML = response.data;
});



setInterval(() => {
    try {
        axios({
            method:"get",
            url:url+"/methods/mqtt"
        }).then((response) => {
            const data = response.data;
            const valor = data.valor;
            const valSplit = valor.split(",");
            console.log(valSplit);


            if(valSplit[0] === "blue" )
            {
                azul = valSplit[1];
                total = valSplit[2];
                listAzul.innerHTML = azul;
                listQnt.innerHTML = total;

            }else if(valSplit[0] === "green"){

                verde = valSplit[1];
                total = valSplit[2];
                listVerd.innerHTML = verde;
                listQnt.innerHTML = total;

            }else if(valSplit[0] === "red"){
                vermelho = valSplit[1];
                total = valSplit[2];
                listVerm.innerHTML = vermelho;
                listQnt.innerHTML = total;
            }
            
            
        })  
    }catch (err) {
        console.log("Servidor foi de arrasta");
    }
},2000);
