window.addEventListener("load", (event) => {
    let a = parseInt(prompt('Entrez la valeur de a :'));
    let b = parseInt(prompt('Entrez la valeur de b :'));
    let r = a + b;
    
    alert("r = " + r);
    
    let para = document.createElement("p");
    para.innerText = "Résultat : " + r;
    document.body.appendChild(para);
  });