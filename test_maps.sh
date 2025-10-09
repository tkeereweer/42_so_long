#! bin/bash

echo "--- Invalid symbols ---"
valgrind ./so_long maps/invalid_symbol.ber
echo ""
echo "--- Invalid walls ---"
valgrind ./so_long maps/invalid_walls.ber
echo ""
echo "--- Multiple exits ---"
valgrind ./so_long maps/multiple_exits.ber
echo ""
echo "--- Multiple players ---"
valgrind ./so_long maps/multiple_players.ber
echo ""
echo "--- No valid path ---"
valgrind ./so_long maps/no_valid_path.ber
echo ""
echo "--- Not a rectangle ---"
valgrind ./so_long maps/not_rectangle.ber
echo ""
echo "--- Zero collectibles ---"
valgrind ./so_long maps/zero_collectibles.ber
echo ""
echo "--- Invalid path ---"
valgrind ./so_long maps/not
echo ""
echo "--- Empty map ---"
valgrind ./so_long maps/empty.ber
