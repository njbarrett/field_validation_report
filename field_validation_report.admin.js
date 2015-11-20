(function ($) {

  Drupal.behaviors.fieldValidationReport = {
    attach: function (context, settings) {
      $('.field-validation-report__entity-type-label').bind('click', function(e) {
        var $entityTypeLabel = $(this);
        var entityType = $(this).closest('.field-validation-report__entity-type').data('entity-type');
        var $bundles = $('.field-validation-report__bundle.field-validation-report__entity-type--' + entityType);
        $bundles.toggle().toggleClass('expanded');
        $(this).toggleClass('expanded');
        $bundles.each(function(i, bundle) {
          if ($entityTypeLabel.hasClass('expanded')) {
            $('.field-validation-report__bundle-label.field-validation-report__bundle--' + $(bundle).data('bundle')).addClass('expanded');
            $('.field-validation-report__entity.field-validation-report__bundle--' + $(bundle).data('bundle')).show();
          }
          else {
            $('.field-validation-report__bundle-label.field-validation-report__bundle--' + $(bundle).data('bundle')).removeClass('expanded');
            $('.field-validation-report__entity.field-validation-report__bundle--' + $(bundle).data('bundle')).hide();
          }
        });
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