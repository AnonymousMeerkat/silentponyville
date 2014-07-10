var width;
var height;
var liheight;
var liamt;

var menu_center = true;

function show_el(element) {
    element.removeClass("hidden");
}

function hide_el(element) {
    element.addClass("hidden");
}

function centerw_el(element) {
    var e_width = element.outerWidth();
    element.offset({
        left: (width - e_width) / 2
    });
}

function centerh_el(element) {
    var e_height = element.outerHeight();
    element.offset({
        top: (height - e_height) / 2
    });
}

function center_el(element) {
    centerw_el(element);
    centerh_el(element);
}

function animate_menu() {
    var $gamemenu = $("#gamemenu");
    var $gamemenu_li = $("#gamemenu li");
    var li_amt = $gamemenu_li.length;
    var spacing = width / li_amt;

    /*for (var i = 0; i < li_amt; i++) {
        var $this = $($gamemenu_li[i]);
        $this.width(spacing);
    }*/

    centerw_el($gamemenu);

    $("#logo").transition({
        opacity: 0,
        duration: 500
    });

    for (var i = 0; i < li_amt; i++) {
        var $this = $($gamemenu_li[i]);
        var offset = $this.offset();
        $this.transition({
            y: -offset.top,
            x: i * spacing - offset.left,
            duration: 700
        });
    }
}

function show_page(name) {
    if (menu_center) {
        animate_menu();
        menu_center = false;
    }

    $(".page").each(function() {
        var $this = $(this);
        if (("#" + $this.attr("id")) !== name && $this.attr("sp_transit") !== "true") {
            $this.transition({
                opacity: 0,
                duration: 1000
            });
            $this.attr("sp_transit", "true");
            setTimeout(function() {if ($this.attr("sp_transit") !== "false") {hide_el($this)}}, 1000);
            $this.css("z-index", 0);
        }
    });

    var $this = $(name);
    if ($this.attr("sp_transit") !== "false") {
        show_el($this);
        $this.transition({
            opacity: 1,
            duration: 1000
        })
        $this.css("z-index", 1000);
        $this.attr("sp_transit", "false");
    }
}

function show_post(name) {
    var $this = $(name);
    if ($this.attr("sp_shown") !== "true") {
        var oldheight = parseInt($this.attr("oldheight"), 10);
        $this.transition({
            height: oldheight,
            duration: 500
        });
        var twopars = $this.parent().parent().parent();
        if ($this.offset().top + oldheight + window.screenY > height) {
            console.log("At ze buttom");
            twopars.scroll();
            twopars.animate({
                scrollTop: twopars.scrollTop() + $this.offset().top + oldheight + window.screenY - height + 26
            }, 500);
            //setTimeout(function() {twopars.scrollTop(twopars.scrollTop() + oldheight)}, 600);
        }
        $this.attr("sp_shown", "true");
    } else {
        $this.transition({
            height: 0,
            duration: 500
        });
        $this.attr("sp_shown", "false");
    }
}

$(document).ready(function() {
    width = $(window).width();
    height = $(window).height();

    var $content = $("#content");
    $content.offset({top: 0, left: 0});
    $content.height(height);

    var liamt = $("#gamemenu li").length;
    var i = 0;

    var spacing = width / liamt;

    $("#gamemenu li").each(function() {
        var $this = $(this);
        liheight = $this.innerHeight();
        $this.offset({left: (width - spacing) / 2, top: (height - (liamt * liheight)) / 2 + i * liheight});
        $this.width(spacing);
        var text = $this.html();
        var page = $this.attr("page");
        $this.attr("onclick", "show_page('#" + page + "');");
        i++;
    });

    //$("#gamemenubg").width(width);
    $("#gamemenubg").height(liheight);

    /*$(".page").offset({
        top: $("#gamemenu").offset().top
    })*/
    $(".page").each(function() {
        var $this = $(this);
        $this.width(width);
        center_el($this);
        if ($this.offset().top < 70) {
            $this.offset({top: 70});
        }
        $this.height(Math.min($this.height() + 5, height - $this.offset().top));
    })
    hide_el($(".page"));

    $(".blog_body").each(function() {
        var $this = $(this);
        $this.attr("oldheight", $this.height());
        $this.css("height", 0);
        $this.parent().children(".blog_title").attr("onclick", "show_post('#" + $this.attr("id") + "');");
    });

    center_el($("#gamemenu"));

    /*center_el($content);
    if ($content.offset().top < 100) {
        $content.offset({top: 100});
    }*/

    var $logo = $("#logo");
    $logo.load(function() {
        $logo.width($logo.width() * .5);
        $logo.offset({
            top: 20 + (($("#gamemenu").offset().top / 2 - $logo.height()) / 2)
        });
        centerw_el($logo);
        show_el($content);
    });
});
