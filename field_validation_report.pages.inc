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
    if ($entity_type === '__count') {
      continue;
    }
    $entity_type_info = entity_get_info($entity_type);
    $rows[] = array(
      'data' => array(
        array(
          'data' => $entity_type_info['label'],
          'class' => array(
            'field-validation-report__entity-type-label',
          ),
        ),
        array(
          'data' => $entity_type_errors['__count'],
          'class' => array(
            $entity_type_errors['__count'] > 0 ? 'error' : 'ok',
          ),
        ),
      ),
      'class' => array(
        'field-validation-report__entity-type',
        'field-validation-report__entity-type--' . drupal_html_class($entity_type),
        $entity_type_errors['__count'] > 0 ? 'error' : 'ok',
      ),
      'data-entity-type' => drupal_html_class($entity_type),
    );
    foreach ($entity_type_errors as $bundle_name => $bundle_errors) {
      if ($bundle_name === '__count') {
        continue;
      }
      $rows[] = array(
        'data' => array(
          array(
            'data' => $entity_type_info['bundles'][$bundle_name]['label'],
            'class' => array(
              'field-validation-report__bundle-label',
              'field-validation-report__bundle--' . drupal_html_class($bundle_name),
            ),
          ),
          array(
            'data' => $bundle_errors['__count'],
            'class' => array(
              $bundle_errors['__count'] > 0 ? 'error' : 'ok',
            ),
          ),
        ),
        'class' => array(
          'field-validation-report__bundle',
          'field-validation-report__entity-type--' . drupal_html_class($entity_type),
          'field-validation-report__bundle--' . drupal_html_class($bundle_name),
          $bundle_errors['__count'] > 0 ? 'error' : 'ok',
        ),
        'data-entity-type' => drupal_html_class($entity_type),
        'data-bundle' => drupal_html_class($bundle_name),
      );
      foreach ($bundle_errors as $entity_id => $entity_errors) {
        if ($entity_id === '__count') {
          continue;
        }
        $entity = entity_load_single($entity_type, $entity_id);
        $uri = entity_uri($entity_type, $entity);
        if ($uri) {
          $entity_label = l(entity_label($entity_type, $entity),
            $uri['path'], $uri['options']);
        }
        else {
          $entity_label = entity_label($entity_type, $entity);
        }

        foreach ($entity_errors as $index => $error) {
          if ($index === '__count') {
            continue;
          }
          $rows[] = array(
            'data' => array(
              array(
                'data' => $entity_label,
                'class' => array(
                  'field-validation-report__entity-label',
                ),
              ),
              array(
                'data' => $error,
                'class' => array(
                  $entity_errors['__count'] > 0 ? 'error' : 'ok',
                ),
              ),
            ),
            'class' => array(
              'field-validation-report__entity',
              'field-validation-report__entity-type--' . drupal_html_class($entity_type),
              'field-validation-report__bundle--' . drupal_html_class($bundle_name),
              $entity_errors['__count'] > 0 ? 'error' : 'ok',
            ),
          );
        }
      }
    }
  }

  $rows[] = array(
    array(
      'header' => TRUE,
      'data' => t('Total Validation Errors'),
    ),
    array(
      'header' => TRUE,
      'data' => $errors['__count'],
    ),
  );

  drupal_add_css(drupal_get_path('module', 'field_validation_report') . '/field_validation_report.admin.css');
  drupal_add_js(drupal_get_path('module', 'field_validation_report') . '/field_validation_report.admin.js');


  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array(
      'class' => array('field-validation-report'),
    ),
  ));

  return $output;
}
