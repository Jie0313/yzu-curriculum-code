$(function(){
    $("input").on("click",function(){
        //alert("hi");
        var count0;
        var count1;
        /*var count2;
        for(var i=0;i<10000;i++){
            var numberOfListItem = $("li").length;
            var randomChildNumber = Math.floor(Math.random()*numberOfListItem);
            if(randomChildNumber==0){
                count0++;
            }
            else if(randomChildNumber==1){
                count1++;
            }
            else if(randomChildNumber==2){
                count2++;
            }
            console.log(randomChildNumber);
            $("h1").text($("li").eq(randomChildNumber).text());
        }*/
        var count = [0,0,0];
        var numberOfListItem = $("li").length;
        for(var i=0;i<10000;i++){
            var randomChildNumber = Math.floor(Math.random()*numberOfListItem);
            count[randomChildNumber]++;
        }
        
        var cnt=0;
        $("li").each(function(){
            $(this).append("<span>"+count[cnt]+"</span>");
            ++cnt;
        })
    });
});