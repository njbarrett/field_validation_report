(function ($) {

  Drupal.behaviors.fieldValidationReport = {
    attach: function (context, settings) {
      $('.field-validation-report__entity-type-label').bind('click', function(e) {
        var entityType = $(this).closest('.field-validation-report__entity-type').data('entity-type');
        $('.field-validation-report__bundle.field-validation-report__entity-type--' + entityType)
          .toggle()
          .toggleClass('expanded');
        $(this).toggleClass('expanded');
      });
      $('.field-validation-report__bundle-label').bind('click', function(e) {
        var bundle = $(this).closest('.field-validation-report__bundle').data('bundle');
        $('.field-validation-report__entity.field-validation-report__bundle--' + bundle)
          .toggle()
          .toggleClass('expanded');
        $(this).toggleClass('expanded');
      });
    }
  };

})(jQuery);