$(document).ready(function(){
    $("div.gallery").hide();
    napravi_div();
    var id=0;
    var imgs=new Array();
    var h1s=$("h1");
    var broj_gradova=h1s.length;
    for(var i=0;i<broj_gradova;i++)
    {
        h1=h1s.eq(i);
        var botun=$("<button id="+i+">Vidi Galeriju</button>").on("click",vidi_galeriju);
        h1.after(botun);
        h1.after("<p>Slike za "+h1.html()+"</p>");
    }
    
    function napravi_div()
    {
        var div=$('<div id="galerija"></div>');
        div.css("position","absolute").css("left","10%").css("top","10%").css("width","80%").css("height","80%")
            .css("background-color","#00008B").css("border","3px solid").css("text-align","center").hide();
        var botun=$("<button>X</button>").on("click",function()
        {
            $("#galerija").hide();
        }).css("position","absolute").css("background-color","red").css("right","0%").css("top","0%");
        var botunLeft=$("<button><<</button>").on("click",nazad).css("position","absolute").css("background-color","green").css("left","5%").css("bottom","5%");
        var botunRight=$("<button>>></button>").on("click",naprijed).css("position","absolute").css("background-color","green").css("right","5%").css("bottom","5%");
        var par1=$('<p id="brojslike"></p>');
        par1.css("position","absolute").css("left","45%").css("color","white").css("bottom","4%");
        var par2=$('<p id="opisslike"></p>');
        par2.css("position","absolute").css("left","45%").css("color","white").css("bottom","1%");
        div.append(botun).append(botunLeft).append(botunRight).append(par1).append(par2);
        $("body").append(div);
    }
    function naprijed()
    {
        for(var i=0;i<imgs.length-1;i++)
        {
            if(imgs[i].is(":visible"))
            {
                imgs[i].hide();
                imgs[i+1].show();
                $("#brojslike").html("Slika "+(i+2)+"/"+imgs.length);
                var paragrafi=$("p");
                for(var j=0;j<paragrafi.length;j++)
                {
                    if(paragrafi.eq(j).attr("data-target")===imgs[i+1].attr("src"))
                    {
                        $("#opisslike").html(paragrafi.eq(j).html());
                        break;
                    }
                }
                return;
            }
        }
    }
    function nazad()
    {
        for(var i=1;i<imgs.length;i++)
        {
            if(imgs[i].is(":visible"))
            {
                imgs[i].hide();
                imgs[i-1].show();
                $("#brojslike").html("Slika "+i+"/"+imgs.length);
                var paragrafi=$("p");
                for(var j=0;j<paragrafi.length;j++)
                {
                    if(paragrafi.eq(j).attr("data-target")===imgs[i-1].attr("src"))
                    {
                        $("#opisslike").html(paragrafi.eq(j).html());
                        break;
                    }
                }
                return;
            }
        }
    }
    function vidi_galeriju()
    {
        for(var i=0;i<imgs.length;i++)
        {
            imgs[i].hide();
        }
        id=$(this).attr("id");
        $("#galerija").show();
        var gal=$("div.gallery").eq(id);
        var children=gal.children();
        imgs.length=0;
        for(var i=0;i<children.length;i++)
        {
            if(children.eq(i).is('img'))
                imgs.push(children.eq(i).clone());
        }
        var strw=$("#galerija").css("width");
        var strh=$("#galerija").css("height");
        var galw=Number(strw.slice(0,-2));
        var galh=Number(strh.slice(0,-2));
        for(var i=0;i<imgs.length;i++)
        {
            var img=imgs[i];
            var w=img.prop("naturalWidth");
            var h=img.prop("naturalHeight");
            img.css("position","absolute").css("top","10%").css("left","10%").hide();
            if(h/galh>w/galw)
            {
                var pom=galh*0.8;//visina
                img.css("width",pom*w/h+"px").css("height",pom+"px");
            }
            else
            {
                var pom=galw*0.8;//sirina
                img.css("width",pom+"px").css("height",pom*h/w+"px");
            }
            $("#galerija").append(img);
            if(i===0)
            {
                img.show();
            }
            
        }
        $("#brojslike").html("Slika 1/"+imgs.length);
        var paragrafi=$("p");
        for(var j=0;j<paragrafi.length;j++)
        {
            if(paragrafi.eq(j).attr("data-target")===imgs[0].attr("src"))
            {
                $("#opisslike").html(paragrafi.eq(j).html());
                break;
            }
        }
    }
 });