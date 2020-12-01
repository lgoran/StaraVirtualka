var nRows=9;
var nCols=9;
var nMines=10;
var id=0;
var width=45;
var height=45;
var broj_dobrih_kucica=nRows*nCols-nMines;
var polje_otkrivenih=[];
$(document).ready(function()
{
    
    igraj();
    $("#nova_igra").click(function()
    {
        if(!isNaN($("#brojRedaka").val()) && $("#brojRedaka").val()!=="")
            nRows=parseInt($("#brojRedaka").val());
        if(!isNaN($("#brojStupaca").val()) && $("#brojStupaca").val()!=="")
            nCols=parseInt($("#brojStupaca").val());
        if(!isNaN($("#brojMina").val()) && $("#brojMina").val()!=="")
            nMines=parseInt($("#brojMina").val());
        if(nRows<1)
            nRows=9;
        if(nRows>20)
            nRows=20;
        if(nCols<1)
            nCols=9;
        if(nCols>20)
            nCols=20;
        if(nMines<0)
            nMines=0;
        if(nMines>=nRows*nCols)
            nMines=nRows*nCols-1;
        broj_dobrih_kucica=nRows*nCols-nMines;
        polje_otkrivenih=[];
        $("#ishod").html("");
        var ctx = $( "#canvas" ).get(0).getContext( "2d" );
        ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
        igraj();
    })
});
function igraj()
{
    for(var i=0;i<nRows*nCols;i++)
    {
        polje_otkrivenih[i]=0;
    }
    crtaj_tablicu();
    dohvati_id();
    $("#canvas").on("contextmenu", function() { return false; });
    $("#canvas").on("mousedown",tipka);
}
function tipka(event)
{
            if(event.button===0)
            {
                odrediKucicu(event,0);//nesto ne stima sa ovakvim pristupon bez on click
            }
            else if(event.button===2)
            {
                odrediKucicu(event,2);
            }
}
function crtaj_tablicu()
{
    var ctx = $( "#canvas" ).get(0).getContext( "2d" );
    ctx.canvas.width=width*nCols;
    ctx.canvas.height=height*nRows;
    ctx.strokeStyle="black";
    ctx.lineWidth = 3;
    ctx.fillStyle="#aaaaaa";
    width=45;
    height=45;
    for(var i=0;i<nRows;i++)
    {
        for(var j=0;j<nCols;j++)
        {
            ctx.strokeRect( j*width, i*height, width, height );
            ctx.fillRect( j*width, i*height, width, height );
        }
    }
}
function dohvati_id()
{
    $.ajax(
    {
        url: 'https://rp2.studenti.math.hr/~zbujanov/dz4/id.php',
        data:
        {
            nRows: nRows,
            nCols: nCols,
            nMines: nMines
        },
        dataType: "json",
        success: function(data)
        {
            id=data["id"];
        },
        error: function(xhr,status)
        {
            console.log("error: Nesto ne valja sa ajax pozivom");
        }  

    }
    )
}
function odrediKucicu(event,klik)
{
    var ctx = $( "#canvas" ).get(0).getContext( "2d" );
    var rect = $( "#canvas" ).get(0).getBoundingClientRect();
    var x = event.clientX - rect.left, y = event.clientY - rect.top;
    var row,col;
    for(var i=0;i<nCols;i++)
    {
        if(x<(i+1)*width)
        {
            col=i;
            break;
        }
    }
    for(var i=0;i<nRows;i++)
    {
        if(y<(i+1)*height)
        {
            row=i;
            break;
        }
    }
    if(klik===0 && polje_otkrivenih[row*nCols+col]===0)
    {
        $.ajax(
            {
                url: "https://rp2.studenti.math.hr/~zbujanov/dz4/cell.php",
                data:
                {
                    id: id,
                    row: row,
                    col: col
                },
                dataType: "json",
                success: function(data)
                {
                    if(data["boom"]==true)
                    {
                        $("#ishod").html("Poraz");
                        $("#canvas").off("mousedown",tipka);
                        
                    }
                    else
                    {
                        nacrtaj_kucice(data["cells"]);
                    }
                },
                error: function(xhr,status)
                {
                    console.log("error: Nesto ne valja sa ajax pozivom");
                }  
            }
            )
    }
    else if(klik===2){
        if(polje_otkrivenih[row*nCols+col]===0)
        {
            ctx.strokeStyle="black";
            ctx.lineWidth = 3;
            ctx.fillStyle="red";
            ctx.fillRect( col*width, row*height, width, height );
            ctx.strokeRect( col*width, row*height, width, height );
            ctx.fillStyle="white";
            ctx.font = "30px Arial";
            ctx.fillText( "?", col*width+width/3, row*height+2*height/3 );
        }
    }
}
function nacrtaj_kucice(cells)
{
    var ctx = $( "#canvas" ).get(0).getContext( "2d" );
    ctx.strokeStyle="black";
    ctx.lineWidth = 3;
    
    for(var i=0;i<cells.length;i++)
    {
        if(polje_otkrivenih[cells[i]["row"]*nCols+cells[i]["col"]]===0)
        {
            var index=cells[i]["row"]*nCols+cells[i]["col"];
            polje_otkrivenih[index]=1;
            ctx.fillStyle="#777777";
            ctx.fillRect( cells[i]["col"]*width, cells[i]["row"]*height, width, height );
            ctx.strokeRect( cells[i]["col"]*width, cells[i]["row"]*height, width, height );
            if(cells[i]["mines"]===1)
                ctx.fillStyle="#00BFFF";
            else if(cells[i]["mines"]===2)
                ctx.fillStyle="#00FF00";
            else if(cells[i]["mines"]===3)
                ctx.fillStyle="red";
            else if(cells[i]["mines"]===4)
                ctx.fillStyle="#800080";
            else if(cells[i]["mines"]===5)
                ctx.fillStyle="black";
            else if(cells[i]["mines"]===6)
                ctx.fillStyle="#800000";
            else if(cells[i]["mines"]===7)
                ctx.fillStyle="#C0C0C0";
            else if(cells[i]["mines"]===8)
                ctx.fillStyle="#40E0D0";
            ctx.font = "30px Arial";
            if(cells[i]["mines"]!==0)
                ctx.fillText( cells[i]["mines"], cells[i]["col"]*width+width/3, cells[i]["row"]*height+2*height/3 );
            broj_dobrih_kucica--;
        }
    }
    if(broj_dobrih_kucica===0)
    {
        $("#ishod").html("Pobjeda");
        $("#canvas").off("mousedown",tipka);
    }
}