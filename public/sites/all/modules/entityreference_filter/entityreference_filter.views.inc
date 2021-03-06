<?php

/**
 * Implements hook_views_data_alter().
 */
function entityreference_filter_views_data_alter(&$data) {
  foreach ($data as $table_name => $table_info) {
    foreach ($table_info as $field_name => $field_info) {
      // Apply to entity reference and term reference fields only.
      if ((strpos($field_name, '_target_id') === FALSE) && (strpos($field_name, '_tid') === FALSE) && ($field_name !== 'nid') && ($field_name !== 'tid') && ($field_name !== 'uid')) {
        continue;
      }
      if (!empty($field_info['filter']['handler']) && $field_info['filter']['handler'] != 'entityreference_filter_view_result') {
        $filter = $field_info;
        $filter['title'] = (!empty($field_info['filter']['title']) ? $field_info['filter']['title'] : $field_info['title']) . ' (reference filter)';
        $filter['filter']['handler'] = 'entityreference_filter_view_result';
        $filter['filter']['proxy'] = $field_info['filter']['handler'];
        $filter['filter']['field'] = $field_name;
        // Organic Groups module uses non-standard fields.
        if ((isset($filter['filter']['table'])) && ($filter['filter']['table'] === 'og_membership')) {
          $filter['filter']['field'] = $field_info['filter']['field'];
        }
        unset($filter['argument'], $filter['field'], $filter['relationship'], $filter['sort'], $filter['filter']['title'], $filter['aliases']);
        $data[$table_name][$field_name . '_entityreference_filter'] = $filter;
      }
    }
  }
}

/**
 * Ajax callback returning ajax commands to update dependent filters.
 */
function entityreference_filter_update_callback($view_name, $display_name, $controlling_filter) {
  $result = array('#type' => 'ajax', '#commands' => array());

  if (empty($_REQUEST['entityreference_filter_form_id'])) {
    return $result;
  }
  // Check that the view is valid and the display still exists.
  $view = views_get_view($view_name);
  if (!$view || !isset($view->display[$display_name]) || !$view->access($display_name)) {
    watchdog('entityreference', 'The view %view_name is no longer eligible for the filter.', array('%view_name' => $view_name), WATCHDOG_WARNING);
    return $result;
  }
  $view->set_display($display_name);

  if (!$view->access(array($display_name))) {
    return $result;
  }

  $view->build();

  $filter_names = array();
  foreach ($view->filter as $filter_handler) {
    if (empty($filter_handler->options['exposed'])) {
      continue;
    }
    $filter_names[$filter_handler->options['expose']['identifier']] = TRUE;
  }

  $filters_to_update = array();
  foreach ($view->filter as $filter_label => $filter_handler) {
    if (!($filter_handler instanceof entityreference_filter_view_result)) {
      continue;
    }
    if (empty($filter_handler->options['exposed'])) {
      continue;
    }
    if (!$filter_handler->dynamic_filter_depends_on($controlling_filter)) {
      continue;
    }
    $filters_to_update[$filter_label] = $filter_handler;
  }

  foreach ($filters_to_update as $filter_label => $filter_handler) {
    $option_str = '';

    $options = $filter_handler->get_value_options();
    foreach ($options as $key => $choice) {
      $key = (string) $key;
      $selected = '';
      $option_str .= '<option value="' . strip_tags($key) . '"' . $selected . '>' . strip_tags($choice) . '</option>';
    }

    if ((empty($filter_handler->always_required)) && (empty($filter_handler->options['expose']['required'])) && (empty($filter_handler->options['expose']['multiple']))) {
      $any_label = variable_get('views_exposed_filter_any_label', 'new_any') == 'old_any' ? t('<Any>') : t('- Any -');

      // Get 'Any' option label defined in Better Exposed Filters.
      $exposed_form = $filter_handler->view->display_handler->get_plugin('exposed_form');
      if (method_exists($exposed_form, '_bef_get_settings')) {
        $bef_settings = $exposed_form->_bef_get_settings();
        if (!empty($bef_settings[$filter_label]['more_options']['any_label'])) {
          $any_label = $bef_settings[$filter_label]['more_options']['any_label'];
        }
      }

      $option_str = '<option value="All">' . check_plain($any_label) . '</option>' . $option_str;
    }

    $filter_name = $filter_handler->options['expose']['identifier'];
    $selector = '#' . $_REQUEST['entityreference_filter_form_id'] . ' [name="' . $filter_name . '"],[name="' . $filter_name . '[]"]';
    $command = ajax_command_html($selector, $option_str);
    $command['command'] = 'entityreference_filter_insertnowrap';
    $result['#commands'][] = $command;

    // If chosen is applied, it can't be updated by attachBehavior().
    $result['#commands'][] = ajax_command_invoke($selector, 'trigger', array('liszt:updated'));
    $result['#commands'][] = ajax_command_invoke($selector, 'trigger', array('chosen:updated'));

    // Options are changed, so run 'change' handlers.
    $result['#commands'][] = ajax_command_invoke($selector, 'trigger', array('change'));
  }

  return $result;
}
