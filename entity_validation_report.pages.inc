<?php

/**
 * @file
 * Page callbacks for Entity Validation Report.
 */

function entity_validation_report_page() {
  $entity_info = entity_get_info();

  foreach ($entity_info as $entity_name => $entity_type) {

    if ($entity_name == 'comment') {
      continue;
    }

    foreach ($entity_type['bundles'] as $bundle_name => $bundle) {

      $query = new \EntityFieldQuery();
      $query->entityCondition('entity_type', $entity_name)
        ->entityCondition('bundle', $bundle_name);

      $results = $query->execute();

      if (!empty($results[$entity_name])) {
        $entities = entity_load($entity_name, array_keys($results[$entity_name]));
        foreach ($entities as $entity) {
          
        }
      }

    }
  }

}