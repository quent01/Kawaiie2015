<?php

/**********************************************************
 * VIEW TEMPLATE FOR THE ARTICLES VIEW OF THA HOME PAGE
 **********************************************************/

/**
 * @file views-bootstrap-grid-plugin-style.tpl.php
 * Default simple view template to display Bootstrap Grids.
 *
 *
 * - $columns contains rows grouped by columns.
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 * - $column_type contains a number (default Bootstrap grid system column type).
 *
 * @ingroup views_templates
 */
?>

<div id="views-bootstrap-grid-<?php print $id ?>" class="<?php print $classes ?>">
  <?php if ($options['alignment'] == 'horizontal'): ?>

    <div class="row">
      <?php foreach ($items as $row): ?>
        <?php foreach ($row['content'] as $column): ?>
          <div class="container-article col col-lg-<?php print $column_type ?> col-md-<?php print $column_type ?> col-sm-6 col-xs-12">
            <?php print $column['content'] ?>
          </div>
        <?php endforeach ?>
      <?php endforeach ?>
    </div>

  <?php else: ?>

    <div class="row">
      <?php foreach ($items as $column): ?>
        <div class="container-article col col-lg-<?php print $column_type ?> col-md-<?php print $column_type ?> col-sm-6 col-xs-12">
          <?php foreach ($column['content'] as $row): ?>
            <?php print $row['content'] ?>
          <?php endforeach ?>
        </div>
      <?php endforeach ?>
    </div>

  <?php endif ?>
</div>