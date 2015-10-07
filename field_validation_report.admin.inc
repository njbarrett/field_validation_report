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

  return system_settings_form($form);
}