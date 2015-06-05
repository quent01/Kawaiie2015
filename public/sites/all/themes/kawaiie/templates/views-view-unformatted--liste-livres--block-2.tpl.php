<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 *
 * TEMPLATE OF THE VIEW THAT DISPLAY BOOK OF 
 * THE SAME SERIE ON A PAGE OF TYPE LIVRE
 *
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<?php foreach ($rows as $id => $row): ?>
	<?php if ( !empty($row[0]) ) : ?>
	   	<div class="container-livre col col-lg-3 col-md -3 col-sm-3 col-xs-4">
			<div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
				<?php print $row; ?>
			</div>
		</div>	
	<?php endif; ?>	
<?php endforeach; ?>