var width;
var height;

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
    var $gamemenu_li = $("#gamemenu li");
    var li_amt = $gamemenu_li.length;
    var spacing = width / li_amt;

    for (var i = 0; i < li_amt; i++) {
        var $this = $($gamemenu_li[i]);
        $this.css({
            "width": spacing
        });
    }

    centerw_el($("#gamemenu"));

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
            $this.css("z-index", 0);
            $this.attr("sp_transit", "true");
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
        $this.transition({
            height: $this.attr("oldheight"),
            duration: 700
        });
        $this.attr("sp_shown", "true");
    } else {
        $this.transition({
            height: 0,
            duration: 700
        });
        $this.attr("sp_shown", "false");
    }
}

$(function() {
    width = $(document).width();
    height = $(document).height();

    $("#gamemenu li").each(function() {
        var $this = $(this);
        var text = $this.html();
        var page = $this.attr("page");
        $this.attr("onclick", "show_page('#" + page + "');");
    });

    $(".page").offset({
        top: $("#gamemenu").offset().top
    })
    hide_el($(".page"));

    $(".blog_body").each(function() {
        var $this = $(this);
        $this.attr("oldheight", $this.height());
        $this.css("height", 0);
        $this.parent().children(".blog_title").attr("onclick", "show_post('#" + $this.attr("id") + "');");
    });

    center_el($("#gamemenu"));

    center_el($("#content"));
    show_el($("#content"));
});
