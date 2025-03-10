window.addEventListener("load",(event) =>{
    let nombre_aleatoire = Math.floor(Math.random() * 100);
    let input_numb;
    do{ 
        input_numb = parseInt(prompt('Devinez le nombre'));
        if(nombre_aleatoire == input_numb){
            alert("Vous avez gagnez");
        }else if(input_numb < nombre_aleatoire ){
            alert("Trop petit");
        }
        else{
            alert("Trop Grand");
        }
    }while(input_numb != nombre_aleatoire);
});