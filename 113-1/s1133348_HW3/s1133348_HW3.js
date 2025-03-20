var interval=null;
var interval2=null;
var count2=0;
var speed2=6;
var count=0;
var speed=6;
var players=["玩家1(藍)","玩家2(綠)","玩家3(紅)","玩家4(黃)"]
var playerMoney=["10000","10000","10000","10000"]
var currentPlayerIndex=-1;
var playerPosition=[0,0,0,0]
var backgroundColor=["blue","green","red","yellow"]
var playerImage=["blue-dot","green-dot","red-dot","yellow-dot"]
var dieValue;
var landProperties = [
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 }, 
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
  { owner: null, landPrice: 1000, houses: 0, housePrice: 500 },  
];

function run()
{
	var x=document.images;
	count+=speed;
	
	var j=Math.floor(1+Math.random()*6);
	x[0].src="die"+j+".png"
	if(count>=150)
	{
		window.clearInterval(interval);
		count=0;
		dieValue=j;
		interval=window.setInterval("moveplayer()",200);
	}
}

function moveplayer(){
	var currentImage;
	count+=speed;
	currentImage=document.getElementById("image"+playerPosition[currentPlayerIndex]);
	var k=currentPlayerIndex;
	var a=0;
	for(var i=0;i<3;i++){
		k=(k+1)%4;
		if(playerPosition[k]==playerPosition[currentPlayerIndex]){
			currentImage.setAttribute("src",playerImage[k]+".png");
			currentImage.setAttribute("alt",playerImage[k]+".png");
			a++;
		}
	}
	if(a==0){
		currentImage.setAttribute("src","");
		currentImage.setAttribute("alt","");
	}
		
	playerPosition[currentPlayerIndex]=(playerPosition[currentPlayerIndex]+1)%20;
	if(playerPosition[currentPlayerIndex]==20)
		playerPosition[currentPlayerIndex]=0;
	currentImage=document.getElementById("image"+playerPosition[currentPlayerIndex]);
	currentImage.setAttribute("src",playerImage[currentPlayerIndex]+".png");
	currentImage.setAttribute("alt",playerImage[currentPlayerIndex]+".png");
	startingPoint();
	
	if(count>=dieValue*6){
		window.clearInterval(interval);
		count=0;
		buildHouse();
		buyLand();
		rent();
		bankrupt();
		interval=null;
		
	}
}

function buyLand(){
	var land=landProperties[playerPosition[currentPlayerIndex]];
	var money=document.getElementById("money"+currentPlayerIndex);
	var cell=document.getElementById("cell"+playerPosition[currentPlayerIndex]);
	if(land.owner==null && playerMoney[currentPlayerIndex]>=land.landPrice && playerPosition[currentPlayerIndex]!=0){
		var result=confirm("你是否要佔領"+playerPosition[currentPlayerIndex]+"號土地?  佔地需要: $"+land.landPrice);
		if(result){
			land.owner=players[currentPlayerIndex];
			playerMoney[currentPlayerIndex]-=land.landPrice;
			
			money.textContent=players[currentPlayerIndex]+"金額: "+playerMoney[currentPlayerIndex];
			cell.innerHTML = "<div class='cell-content'>" +
							playerPosition[currentPlayerIndex] + "  (" + land.houses + "層)" +
							"<img id='image" + playerPosition[currentPlayerIndex] + "' src='" + playerImage[currentPlayerIndex] + ".png' alt='" + playerImage[currentPlayerIndex] + ".png'>"+"</div>";

			alert("恭喜! 你成功佔領"+playerPosition[currentPlayerIndex]+"號土地");
			cell.setAttribute("style","background-color: "+backgroundColor[currentPlayerIndex]);
		}
	}
	else if(land.owner==null && !(playerMoney[currentPlayerIndex]>=land.landPrice))
		alert("你無足夠的金錢佔領該地");
}

function buildHouse(){
	var land=landProperties[playerPosition[currentPlayerIndex]];
	var money=document.getElementById("money"+currentPlayerIndex);
	var cell=document.getElementById("cell"+playerPosition[currentPlayerIndex]);
	if(land.owner==players[currentPlayerIndex] && land.houses<=5 &&playerMoney[currentPlayerIndex]>=land.housePrice){
		var result=confirm("你是否要蓋房?  蓋房需要: $500" );
		if(result){
			land.houses+=1;
			playerMoney[currentPlayerIndex]-=land.housePrice;
			money.textContent=players[currentPlayerIndex]+"金額: "+playerMoney[currentPlayerIndex];
			cell.innerHTML = "<div class='cell-content'>" +
							playerPosition[currentPlayerIndex] + "  (" + land.houses + "層)" +
							"<img id='image" + playerPosition[currentPlayerIndex] + "' src='" + playerImage[currentPlayerIndex] + ".png' alt='" + playerImage[currentPlayerIndex] + ".png'>"+"</div>";

			alert("恭喜! 蓋房成功");
		}
		
	}
	else if(land.owner==players[currentPlayerIndex] && !(playerMoney[currentPlayerIndex]>=land.landPrice))
		alert("你無足夠的金錢蓋房");
	
}

function rent(){
	var land=landProperties[playerPosition[currentPlayerIndex]];
	var money=document.getElementById("money"+currentPlayerIndex);
	var k=currentPlayerIndex;
	for(var i=0;i<3;i++){
		k=(k+1)%4;
		if(land.owner==players[k]){
			playerMoney[currentPlayerIndex]-=(1+land.houses)*500;
			playerMoney[k]+=(1+land.houses)*500;
			alert("你踩到"+players[k]+"的土地 需支付租金$"+(1+land.houses)*500);
			var rent=document.getElementById("money"+k);
			money.textContent=players[currentPlayerIndex]+"金額: "+playerMoney[currentPlayerIndex];
			rent.textContent=players[k]+"金額: "+playerMoney[k];
			break;
		}
	}
}

function startingPoint(){
	var money=document.getElementById("money"+currentPlayerIndex);
	if(playerPosition[currentPlayerIndex]==0){
		playerMoney[currentPlayerIndex]+=2000;
		alert("經過起始點加$2000");
		money.textContent=players[currentPlayerIndex]+"金額: "+playerMoney[currentPlayerIndex];
	}
	
}

function bankrupt(){
	var money=document.getElementById("money"+currentPlayerIndex);
	var currentImage=document.getElementById("image"+playerPosition[currentPlayerIndex]);
	var k=currentPlayerIndex;
	var a=0;
	if(playerMoney[currentPlayerIndex]<0){
		money.textContent=players[currentPlayerIndex]+"金額: 已破產";
		for(var i=0;i<3;i++){
			k=(k+1)%4;
			if(playerPosition[k]==playerPosition[currentPlayerIndex]){
				currentImage.setAttribute("src",playerImage[k]+".png");
				currentImage.setAttribute("alt",playerImage[k]+".png");
				a++;
			}
		}
		if(a==0){
			currentImage.setAttribute("src","");
			currentImage.setAttribute("alt","");
		}
		playerPosition[currentPlayerIndex]=-1;
		playerMoney[currentPlayerIndex]=-9999999;
	}
	
	
}

function display()
{
	var currentPlayer=document.getElementById("currentPlayer");
	if(interval)
		return;
	currentPlayerIndex=(currentPlayerIndex+1)%players.length;
	while(playerMoney[currentPlayerIndex]<0){
		currentPlayerIndex=(currentPlayerIndex+1)%players.length;
	}
	currentPlayer.textContent="當前玩家: "+players[currentPlayerIndex];
	if(currentPlayerIndex==4)
		currentPlayerIndex=0;
	if(playerPosition[currentPlayerIndex]==0){
		currentImage=document.getElementById("image0");
		currentImage.setAttribute("src",playerImage[currentPlayerIndex]+".png");
		currentImage.setAttribute("alt",playerImage[currentPlayerIndex]+".png");	
	}
	interval=window.setInterval("run()",50);
}

function start()
{
	document.getElementById("Button").addEventListener("click",display,false);
}

window.addEventListener("load",start,false);