//--------------------------------------------------------------------------------
// private methods
static void draw_piece_line(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc);
static void draw_piece_l_left(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc);
static void draw_piece_l_right(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc);
static void draw_piece_square(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc);
static void draw_piece_z_left(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc);
static void draw_piece_t(struct tetris_piece_blocks* const tetris_piece_blocks,
                         const struct tetris_piece_desc tetris_piece_desc);
static void draw_piece_z_right(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc);

//--------------------------------------------------------------------------------
static void draw_piece_line(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
    tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
  }
  if (tetris_piece_desc.rotation % 2) {
    for (i = 1; i < tetris_piece_block_nb; ++i) {
      tetris_piece_blocks->blocks[i].x += i;
    }
  } else {
    for (i = 1; i < tetris_piece_block_nb; ++i) {
      tetris_piece_blocks->blocks[i].y += i;
    }
  }
}

//--------------------------------------------------------------------------------
static void draw_piece_l_left(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
//MDTMP rotation
  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
    tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
  }

  // horizontal line of 3
  for (i = 1; i < tetris_piece_block_nb - 1; ++i) {
    tetris_piece_blocks->blocks[i].x += i;
  }
  // + 1 top left
  ++tetris_piece_blocks->blocks[3].y;
}

//--------------------------------------------------------------------------------
static void draw_piece_l_right(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
//MDTMP rotation
  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
    tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
  }

  // horizontal line of 3
  for (i = 1; i < tetris_piece_block_nb - 1; ++i) {
    tetris_piece_blocks->blocks[i].x += i;
  }
  // + 1 top right
  tetris_piece_blocks->blocks[3].x = tetris_piece_blocks->blocks[2].x;
  ++tetris_piece_blocks->blocks[3].y;
}

//--------------------------------------------------------------------------------
static void draw_piece_square(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
    tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
  }

  ++tetris_piece_blocks->blocks[1].x;
  ++tetris_piece_blocks->blocks[2].y;
  ++tetris_piece_blocks->blocks[3].x;
  ++tetris_piece_blocks->blocks[3].y;
}

//--------------------------------------------------------------------------------
static void draw_piece_z_left(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
//MDTMP rotation
  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
    tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
  }

  ++tetris_piece_blocks->blocks[1].x;
  tetris_piece_blocks->blocks[2].x = tetris_piece_blocks->blocks[1].x;
  ++tetris_piece_blocks->blocks[2].y;
  tetris_piece_blocks->blocks[3].x = tetris_piece_blocks->blocks[2].x + 1;
  tetris_piece_blocks->blocks[3].y = tetris_piece_blocks->blocks[2].y;
}

//--------------------------------------------------------------------------------
static void draw_piece_t(struct tetris_piece_blocks* const tetris_piece_blocks,
                         const struct tetris_piece_desc tetris_piece_desc) {
//MDTMP rotation
  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
    tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
  }

  // horizontal line of 3
  for (i = 1; i < tetris_piece_block_nb - 1; ++i) {
    tetris_piece_blocks->blocks[i].x += i;
  }
  // + 1 top middle
  ++tetris_piece_blocks->blocks[3].x;
  ++tetris_piece_blocks->blocks[3].y;
}

//--------------------------------------------------------------------------------
static void draw_piece_z_right(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
//MDTMP rotation
  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
    tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
  }

  ++tetris_piece_blocks->blocks[0].y;
  tetris_piece_blocks->blocks[1].y = tetris_piece_blocks->blocks[0].y;
  ++tetris_piece_blocks->blocks[1].x;
  tetris_piece_blocks->blocks[2].x = tetris_piece_blocks->blocks[1].x;
  tetris_piece_blocks->blocks[3].x = tetris_piece_blocks->blocks[2].x + 1;
}
