<?php

/**
 * @file
 * Page callbacks for Field Validation Report.
 */

function field_validation_report_page() {
  // Loop over configuration, if bundle is enabled then run the validations.
  foreach (field_validation_report_entities_enabled() as $entity_type => $bundles) {
    if (!$bundles) {
      continue;
    }

    foreach ($bundles as $bundle_name => $bundle_enabled) {
      if (!$bundle_enabled) {
        continue;
      }

      _field_validation_report_validate_bundle($entity_type, $bundle_name);
    }
  }

  $header = array(
    t('Entity'),
    t('Entity Type'),
    t('Bundle'),
    t('Error'),
  );

  $errors = _field_validation_report_get_errors();
  $rows = array();
  foreach ($errors as $error) {
    $uri = entity_uri($error['entity_type'], $error['entity']);
    if ($uri) {
      $entity_label = l(entity_label($error['entity_type'], $error['entity']),
        url($uri['path'], $uri['options']));
    }
    else {
      $entity_label = entity_label($error['entity_type'], $error['entity']);
    }
    $rows[] = array(
      $entity_label,
      $error['entity_type'],
      $error['bundle'],
      $error['message'],
    );
  }

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));

  return $output;
}