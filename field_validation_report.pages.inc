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

//  $form_state = array(
//    'programmed' => TRUE,
//    'build_info' => array(
//      'args' => array(
//        0 => 'node',
//        1 => node_load(1),
//      ),
//    ));
//
//  $form = drupal_build_form('field_validation_report_pseudo_form', $form_state);
//
//  return $form;
}