$(function(){
    $("#courseTable").empty();
    $("#courseTable").append("<tr><th>場次</th><th>時間</th><th>主題</th></tr>");

    var topicCount = topic.length;
    console.log(topicCount);

    let millisecsPerDay = 24*60*60*1000;

    for(var x=0;x<topicCount;x++){
        let isCanceled = topic[x].includes("停課") ? 'class="gray-bg"' : '';
        $("#courseTable").append(
            `<tr ${isCanceled}>`+
            `<td>${x+1}</td>`+
            `<td>${(new Date(startDate.getTime()+7*x*millisecsPerDay)).toLocaleDateString(undefined, { month: '2-digit', day: '2-digit' })}</td>` +
            `<td>${topic[x]}</td>`+
            "</tr>"
        );
    }

});