struct position
{
        int x;
        int y;
};

enum mStatus
{
        dead_end,
        fork,
        box,
        corridor,
        end,
        angle,
};

enum direction 
{
        down,
        up,
        right,
        left,
        d_null
};
