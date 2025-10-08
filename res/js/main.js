const openRules = document.querySelector(".open-rules");
const rulesModel = document.querySelector(".rules-modal");
const closeRules = document.querySelector(".close-rules");
const openForm = document.querySelector(".open-form");
const formModel = document.querySelector(".form-modal");
const closeForm = document.querySelector(".close-form");

openRules.onclick = () => {
    rulesModel.style.display = "flex";
}

closeRules.onclick = () => {
    rulesModel.style.display = "none";
}

openForm.onclick = () => {
    formModel.style.display = "flex";
}

closeForm.onclick = () => {
    formModel.style.display = "none";
}