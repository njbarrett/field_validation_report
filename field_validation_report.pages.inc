<?php

/**
 * @file
 * Page callbacks for Field Validation Report.
 */

function field_validation_report_page() {
  _field_validation_report_validate_entity_type('node');

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