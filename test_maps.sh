#! bin/bash

echo "--- Invalid symbols ---"
./so_long maps/invalid_symbol.ber
echo ""
echo "--- Invalid walls ---"
./so_long maps/invalid_walls.ber
echo ""
echo "--- Multiple exits ---"
./so_long maps/multiple_exits.ber
echo ""
echo "--- Multiple players ---"
./so_long maps/multiple_players.ber
echo ""
echo "--- No valid path ---"
./so_long maps/no_valid_path.ber
echo ""
echo "--- Not a rectangle ---"
./so_long maps/not_rectangle.ber
echo ""
echo "--- Zero collectibles ---"
./so_long maps/zero_collectibles.ber
echo ""
echo "--- Valid map ---"
./so_long maps/map1.ber
