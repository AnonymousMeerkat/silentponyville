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
            "width": spacing - 1
        });
        centerw_el($("#content"));
        var offset = $this.offset();
        $this.transition({
            y: -offset.top,
            x: i * spacing - offset.left,
            duration: 700
        })
    }
}

function show_page(name) {
    if (menu_center) {
        animate_menu();
        menu_center = false;
    }

    $(".page").each(function() {
        var $this = $(this);
        if (("#" + $this.attr("id")) !== name) {
            $this.transition({
                opacity: 0,
                duration: 1000
            });
            $this.css("z-index", 0);
        }
    });

    var $this = $(name);

    show_el($this);
    $this.transition({
        opacity: 1,
        duration: 1000
    })
    $this.css("z-index", 1000);
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

    center_el($("#content"));
    show_el($("#content"));
});
