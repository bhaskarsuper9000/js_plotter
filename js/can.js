function Point(x,y)
{
	this.x = x;
	this.y = y;
	
	this.plot=plot;
	function plot(ctx)
	{
		ctx.fillStyle='#000000';
		ctx.moveTo(this.x, this.y);
		//ctx.lineTo(this.x+1,this.y+1);
		//ctx.stroke();
		ctx.beginPath();
		ctx.arc(this.x,this.y,2,0,2*Math.PI);
		ctx.closePath();
		ctx.fill();
	}
}

function line(x1,y1,x2,y2)
{
	ctx=document.getElementById('vis').getContext('2d');
	ctx.moveTo(x1,y1);
	ctx.lineTo(x2,y2);
	ctx.stroke();
}

function circle(x,y,r)
{
	ctx=document.getElementById('vis').getContext('2d');
	ctx.beginPath();
	ctx.arc(x,y,r,0,2*Math.PI);
	ctx.closePath();
	ctx.stroke();
}

function rectangle(x,y,w,h)
{
	ctx=document.getElementById('vis').getContext('2d');
	ctx.beginPath();
	ctx.moveTo(x,y);
	ctx.lineTo(x+w,y);
	ctx.lineTo(x+w,y+h);
	ctx.lineTo(x,y+h);
	ctx.closePath();
	ctx.stroke();
	
}

function clear()
{
	can=document.getElementById('vis');
	can.getContext('2d').clearRect(0,0,can.width,can.height);
}

function yo()
{
	var canvas=document.getElementById('vis');
	var ctx=canvas.getContext('2d');
	//ctx.fillStyle='#FF0000';
	//ctx.fillRect(0,0,80,100);
	
	var point = new Point(100,100);
	var p2 = new Point(200,20);
	
	point.plot(ctx);
	//setTimeout(clicked,100);
}

function clicked()
{
	//for(var i=0; i<500; i++)
	//{
		//$('#result').load('./js/temp/plot'+i+'.js?');
		$.ajax({
		  url: './js/temp/plot.js',
		  dataType: 'script',
		  contentType: 'text/javascript'
		  }).done( function( data ) {
		    //alert('Yo');
			$( '#exec' ).append(data);
		  }).fail( function(jqXHR, textStatus) {
		  	alert("Coudn't load js"+textStatus);
		  })
		;
	//}
	
	/*
	var request = $.ajax({
	  type: "GET",
	  url: "./js/temp/plot1.js",
	  dataType: "script"
	});
 
	request.done(function( msg ) {
	  $( "#log" ).html( msg );
	});
	setTimeout(callback_plot, 15000);
	*/
}

function callback_plot()
{
	//$('#exec').append($('#result').text());
	eval($('#exec').text());
}
