<?php
/**
 * @file
 * Contains admin functionality for the field validation report module.
 */

/**
 * Page callback for the field validation report configuration.
 */
function field_validation_report_config() {
  $form = array();

  $form['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'field_validation_report') . '/field_validation_report.admin.css',
    ),
  );

  $form['entities'] = array(
    '#type' => 'fieldset',
    '#title' => t('Master controls for all entities'),
    '#description' => t("By enabling and disabling items here, it is possible to control which entities (e.g. nodes, taxonomy terms) and bundles (e.g. content types, vocabularies) will have the appear in the field validation report. If an entity type is disabled it also disables it for <em>all</em> of that entity type's bundles.<br />Technical note: Entity types must be fieldable and must not be configuration entities."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  foreach (entity_get_info() as $entity_type => $entity_info) {
    // Only show entities that are capable of using meta tags.
    if (field_validation_report_entity_type_is_suitable($entity_type, $entity_info)) {
      $entity_enabled = field_validation_report_entity_supports_validation($entity_type);
      $form['entities']['field_validation_report_enable_' . $entity_type] = array(
        '#type' => 'checkbox',
        '#title' => t($entity_info['label']),
        '#default_value' => $entity_enabled,
      );

      // Some entities, e.g. User, (core) File, have a single bundle with the
      // same name as the entity, so only show the bundles list if there is
      // more than one of them and the bundle's name isn't the same as the
      // entity type's.
      if (!empty($entity_info['bundles'])) {
        foreach ($entity_info['bundles'] as $bundle_name => $bundle_info) {
          if (count($entity_info['bundles']) > 1 || $entity_type != $bundle_name) {
            // If the entity type was disabled, automatically enable the bundle.
            // This will have the effect that if the entity type is enabled in
            // the form then all of the bundles will then also be enabled. This
            // is safe to do because in the rest of the module the bundle will
            // be ignored if the entity is disabled.
            $form['entities']['field_validation_report_enable_' . $entity_type . '__' . $bundle_name] = array(
              '#type' => 'checkbox',
              '#title' => t($bundle_info['label']),
              '#default_value' => !$entity_enabled || field_validation_report_entity_supports_validation($entity_type, $bundle_name),
              '#attributes' => array(
                // Add some theming that'll indent this bundle.
                'class' => array('field-validation-report-bundle-checkbox'),
              ),
              '#states' => array(
                'visible' => array(
                  ':input[name="field_validation_report_enable_' . $entity_type . '"]' => array('checked' => TRUE),
                ),
              ),
            );
          }
        }
      }
    }
  }

  return system_settings_form($form);
}