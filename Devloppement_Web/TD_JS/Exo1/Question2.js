window.addEventListener("load",(event)=>{
    console.log("page loaded");
    let i = parseInt(prompt('entrez la valeur de i : '));
    for(j=1;j<=i;j++){
        let para = document.createElement("p");
        for(k=0;k<j;k++){
            para.textContent += j;
        }
        document.body.appendChild(para);
    }
});