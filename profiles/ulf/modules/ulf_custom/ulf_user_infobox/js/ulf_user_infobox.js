(function ($) {
  Drupal.behaviors.ulf_user_infobox = {
    attach:function (context) {
      $.ajax({
        type: 'GET',
        url: '/ulf_infobox/get/ajax',
        dataType: 'json',
        success: function(data) {
          if ($('.infobox-wrapper').length > 0) {
            $('.infobox-wrapper').remove();
          }
          $('.page--messages').after(data);
        }
      });
    }
  }
})(jQuery);
