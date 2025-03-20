let topic = [
    "課程介紹",
    "開發環境&今天晚餐吃什麼",
    "課程時間表",
    "心理測驗",
    "心理測驗Python版",
    "停課-講師出差",
    "停課-元智校慶補假",
    "Simple RPG"
];

let inputMonth, inputDay;
let startDate = new Date();
console.log(startDate);

function setMonthAndDate(startMonth, startDay){
    console.log("[setMonthAndDay] called")
    startDate.setMonth(startMonth-1, startDay)
    startDate.setHours(0);
    startDate.setMinutes(0);
    startDate.setSeconds(0);
}

document.addEventListener('DOMContentLoaded', function() {
    const inputDate = document.getElementById('inputDate');

    inputDate.addEventListener('change', function() {
        console.log("[inputDate] Being Called");

        const dateValue = inputDate.value;
        const dateParts = dateValue.split('-');

        inputMonth = parseInt(dateParts[1], 10);
        inputDay = parseInt(dateParts[2], 10);

        setMonthAndDate( inputMonth, inputDay );

        const courseTable = document.getElementById('courseTable');
        courseTable.innerHTML = '<tr><th>Session</th><th>Time</th><th>Theme</th></tr>';

        for (let i = 0; i < topic.length; i++) {
            const tr = document.createElement('tr');
            const tdSession = document.createElement('td');
            const tdDate = document.createElement('td');
            const tdTopic = document.createElement('td');

            const currentDate = new Date(startDate);
            currentDate.setDate(startDate.getDate() + i*7);

            tdSession.textContent = i + 1;
            tdDate.textContent = currentDate.toLocaleDateString('en-US', { month: 'numeric', day: 'numeric' });
            tdTopic.textContent = topic[i];

            tr.appendChild(tdSession);
            tr.appendChild(tdDate);
            tr.appendChild(tdTopic);
            courseTable.appendChild(tr);
            
            if (topic[i].includes("停課")) {
                tr.style.backgroundColor = "rgb(168, 168, 168)";
            }
        }
    });
});


