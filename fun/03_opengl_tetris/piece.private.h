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
    if (tetris_piece_desc.rotation % 2) {
      tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x - 1 + i;
      tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
    } else {
      tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y + i;
    }
  }
}

//--------------------------------------------------------------------------------
static void draw_piece_l_left(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
  size_t i;
  for (i = 0; i < tetris_piece_block_nb - 1; ++i) {
    switch(tetris_piece_desc.rotation)
    {
      case PIECE_ROT_0:
        tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
        tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y + i;
        break;
      case PIECE_ROT_1:
        tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x - 1 + i;
        tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
        break;
      case PIECE_ROT_2:
        tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
        tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y + i;
        break;
      case PIECE_ROT_3:
        tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x - 1 + i;
        tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y + 1;
        break;
      case PIECE_ROT_NB_MAX:
        assert(0);
    }
  }

  switch(tetris_piece_desc.rotation)
  {
    case PIECE_ROT_0:
      tetris_piece_blocks->blocks[3].x =
          tetris_piece_desc.position.x - 1;
      tetris_piece_blocks->blocks[3].y =
          tetris_piece_desc.position.y;
      break;
    case PIECE_ROT_1:
      tetris_piece_blocks->blocks[3].x =
          tetris_piece_desc.position.x - 1;
      tetris_piece_blocks->blocks[3].y =
          tetris_piece_desc.position.y + 1;
      break;
    case PIECE_ROT_2:
      tetris_piece_blocks->blocks[3].x =
          tetris_piece_desc.position.x + 1;
      tetris_piece_blocks->blocks[3].y =
          tetris_piece_desc.position.y + 2;
      break;
    case PIECE_ROT_3:
      tetris_piece_blocks->blocks[3].x =
          tetris_piece_desc.position.x + 1;
      tetris_piece_blocks->blocks[3].y =
          tetris_piece_desc.position.y;
      break;
    case PIECE_ROT_NB_MAX:
      assert(0);
  }
}

//--------------------------------------------------------------------------------
static void draw_piece_l_right(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
  size_t i;
  for (i = 0; i < tetris_piece_block_nb - 1; ++i) {
    switch(tetris_piece_desc.rotation)
    {
      case PIECE_ROT_0:
        tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
        tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y + i;
        break;
      case PIECE_ROT_1:
        tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x - 1 + i;
        tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y + 1;
        break;
      case PIECE_ROT_2:
        tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x;
        tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y + i;
        break;
      case PIECE_ROT_3:
        tetris_piece_blocks->blocks[i].x = tetris_piece_desc.position.x - 1 + i;
        tetris_piece_blocks->blocks[i].y = tetris_piece_desc.position.y;
        break;
      case PIECE_ROT_NB_MAX:
        assert(0);
    }
  }

  switch(tetris_piece_desc.rotation)
  {
    case PIECE_ROT_0:
      tetris_piece_blocks->blocks[3].x =
          tetris_piece_desc.position.x + 1;
      tetris_piece_blocks->blocks[3].y =
          tetris_piece_desc.position.y;
      break;
    case PIECE_ROT_1:
      tetris_piece_blocks->blocks[3].x =
          tetris_piece_desc.position.x - 1;
      tetris_piece_blocks->blocks[3].y =
          tetris_piece_desc.position.y;
      break;
    case PIECE_ROT_2:
      tetris_piece_blocks->blocks[3].x =
          tetris_piece_desc.position.x - 1;
      tetris_piece_blocks->blocks[3].y =
          tetris_piece_desc.position.y + 2;
      break;
    case PIECE_ROT_3:
      tetris_piece_blocks->blocks[3].x =
          tetris_piece_desc.position.x + 1;
      tetris_piece_blocks->blocks[3].y =
          tetris_piece_desc.position.y + 1;
      break;
    case PIECE_ROT_NB_MAX:
      assert(0);
  }
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
  switch(tetris_piece_desc.rotation)
  {
    case PIECE_ROT_0:
    case PIECE_ROT_2:
      tetris_piece_blocks->blocks[0].x = tetris_piece_desc.position.x-1;
      tetris_piece_blocks->blocks[0].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[1].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[1].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[2].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[2].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[3].x = tetris_piece_desc.position.x+1;
      tetris_piece_blocks->blocks[3].y = tetris_piece_desc.position.y+1;
      break;
    case PIECE_ROT_1:
    case PIECE_ROT_3:
      tetris_piece_blocks->blocks[0].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[0].y = tetris_piece_desc.position.y+2;
      tetris_piece_blocks->blocks[1].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[1].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[2].x = tetris_piece_desc.position.x+1;
      tetris_piece_blocks->blocks[2].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[3].x = tetris_piece_desc.position.x+1;
      tetris_piece_blocks->blocks[3].y = tetris_piece_desc.position.y;
      break;
    case PIECE_ROT_NB_MAX:
      assert(0);
  }
}

//--------------------------------------------------------------------------------
static void draw_piece_t(struct tetris_piece_blocks* const tetris_piece_blocks,
                         const struct tetris_piece_desc tetris_piece_desc) {
  switch(tetris_piece_desc.rotation)
  {
    case PIECE_ROT_0:
      tetris_piece_blocks->blocks[0].x = tetris_piece_desc.position.x-1;
      tetris_piece_blocks->blocks[0].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[1].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[1].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[2].x = tetris_piece_desc.position.x+1;
      tetris_piece_blocks->blocks[2].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[3].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[3].y = tetris_piece_desc.position.y+1;
break;
    case PIECE_ROT_1:
      tetris_piece_blocks->blocks[0].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[0].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[1].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[1].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[2].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[2].y = tetris_piece_desc.position.y+2;
      tetris_piece_blocks->blocks[3].x = tetris_piece_desc.position.x+1;
      tetris_piece_blocks->blocks[3].y = tetris_piece_desc.position.y+1;
break;
    case PIECE_ROT_2:
      tetris_piece_blocks->blocks[0].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[0].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[1].x = tetris_piece_desc.position.x-1;
      tetris_piece_blocks->blocks[1].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[2].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[2].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[3].x = tetris_piece_desc.position.x+1;
      tetris_piece_blocks->blocks[3].y = tetris_piece_desc.position.y+1;
      break;
    case PIECE_ROT_3:
      tetris_piece_blocks->blocks[0].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[0].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[1].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[1].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[2].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[2].y = tetris_piece_desc.position.y+2;
      tetris_piece_blocks->blocks[3].x = tetris_piece_desc.position.x-1;
      tetris_piece_blocks->blocks[3].y = tetris_piece_desc.position.y+1;
      break;
    case PIECE_ROT_NB_MAX:
      assert(0);
  }
}

//--------------------------------------------------------------------------------
static void draw_piece_z_right(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
  switch(tetris_piece_desc.rotation)
  {
    case PIECE_ROT_0:
    case PIECE_ROT_2:
      tetris_piece_blocks->blocks[0].x = tetris_piece_desc.position.x-1;
      tetris_piece_blocks->blocks[0].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[1].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[1].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[2].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[2].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[3].x = tetris_piece_desc.position.x+1;
      tetris_piece_blocks->blocks[3].y = tetris_piece_desc.position.y;
      break;
    case PIECE_ROT_1:
    case PIECE_ROT_3:
      tetris_piece_blocks->blocks[0].x = tetris_piece_desc.position.x-1;
      tetris_piece_blocks->blocks[0].y = tetris_piece_desc.position.y;
      tetris_piece_blocks->blocks[1].x = tetris_piece_desc.position.x-1;
      tetris_piece_blocks->blocks[1].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[2].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[2].y = tetris_piece_desc.position.y+1;
      tetris_piece_blocks->blocks[3].x = tetris_piece_desc.position.x;
      tetris_piece_blocks->blocks[3].y = tetris_piece_desc.position.y+2;
      break;
    case PIECE_ROT_NB_MAX:
      assert(0);
  }
}
