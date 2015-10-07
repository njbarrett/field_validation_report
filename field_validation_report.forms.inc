<?php

/**
 * @file
 * Form callbacks for the Field Validation Report module.
 */

function field_validation_report_pseudo_form($form, &$form_state, $entity_type, $entity) {
  // During initial form build, add the entity and entity type to the form state for use during
  // form building and processing. During a rebuild, use what is in the form
  // state.
  if (!isset($form_state[$entity_type])) {
    $form_state[$entity_type] = $entity;
    $form_state['entity_type'] = $entity_type;
  }
  else {
    $entity = $form_state[$entity_type];
  }

  // Add field widgets.
  field_attach_form($entity_type, $entity, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'submit',
  );

  unset($form['#token']);

  return $form;
}