const generaScuseFamiglia = document.querySelector(".generaScuseFamiglia")
const generaScuseDeveloper = document.querySelector(".generaScuseDeveloper")
const generaScuseUfficio = document.querySelector(".generaScuseUfficio")

const scuseGenerate = document.querySelector(".scuseGenerate")
generaScuseFamiglia.addEventListener("click", function (){
    fetchScuse("family")
})

generaScuseDeveloper.addEventListener("click", function (){
    fetchScuse("developers")
})

generaScuseUfficio.addEventListener("click", function (){
    fetchScuse("office")
})

const fetchScuse = (type) => {
    const url = `https://excuser-three.vercel.app/v1/excuse/${type}`
    scuseGenerate.textContent = "Generando scusa..."
    fetch(url)
        .then(res => res.json())
        .then(data => {
            translateToItalian(data[0]["excuse"])
        })

}

const translateToItalian = (text) => {
    const url = `https://api.mymemory.translated.net/get?q=${encodeURIComponent(text)}&langpair=en|it`;
    fetch(url)
        .then(res => res.json())
        .then(data => {
            const translatedText = data.responseData.translatedText
            scuseGenerate.textContent = translatedText
        })
}
let arr = [2, 4, 5]
arr.forEach((val, index, arr)=> {
    arr[index]+=1
})
console.log(arr);