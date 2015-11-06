<?php

/**
 * @file
 * Page callbacks for Field Validation Report.
 */

function field_validation_report_page() {
  // Run the validations.
  field_validation_report_run_validations();

  $header = array(
    t('Entity'),
    t('Validation Errors'),
  );

  $errors = _field_validation_report_get_errors();
  $rows = array();
  foreach ($errors as $entity_type => $entity_type_errors) {
    $entity_type_info = entity_get_info($entity_type);
    $rows[] = array(
      array(
        'data' => $entity_type_info['label'],
        'class' => array('field-validation-report__entity-type'),
      ),
      $entity_type_errors['__count'],
    );
    foreach ($entity_type_errors as $bundle_name => $bundle_errors) {
      if ($bundle_name == '__count') {
        continue;
      }
      $rows[] = array(
        array(
          'data' => $entity_type_info['bundles'][$bundle_name]['label'],
          'class' => array('field-validation-report__bundle'),
        ),
        $bundle_errors['__count'],
      );
      foreach ($bundle_errors as $entity_id => $entity_errors) {
        if ($entity_id == '__count') {
          continue;
        }
        $entity = entity_load_single($entity_type, $entity_id);
        $uri = entity_uri($entity_type, $entity);
        if ($uri) {
          $entity_label = l(entity_label($entity_type, $entity),
            url($uri['path'], $uri['options']));
        }
        else {
          $entity_label = entity_label($entity_type, $entity);
        }

        foreach ($entity_errors as $error) {
          $rows[] = array(
            array(
              'data' => $entity_label,
              'class' => array('field-validation-report__entity'),
            ),
            $error,
          );
        }
      }
    }
  }

  drupal_add_css(drupal_get_path('module', 'field_validation_report') . '/field_validation_report.admin.css');

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));

  return $output;
}
