using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PLGridConnectionApp
{
    class SegmentOptions
    {
        public int SMMinSize { get; set; } = 0;
        public int SMVariant { get; set; } = 0;
        public int SMAverage { get; set; } = 0;

        public int LinesWidth { get; set; } = 0;
        public int LinesHeight { get; set; } = 0;

        public int RoundWidth { get; set; } = 0;
        public int RoundHeight { get; set; } = 0;

        public int RoundX { get; set; } = 0;
        public int RoundY { get; set; } = 0;
        public int RoundR { get; set; } = 0;
        public int RoundTrshld { get; set; } = 0;

        public int FiguresWidth { get; set; } = 0;
        public int FiguresHeight { get; set; } = 0;

        public string FiguresPatternPath { get; set; } = "";

        public SegmentOptions(int smms, int smv, int sma, int w, int h, int x, int y, int r, int trsh, string path)
        {
            SMMinSize = smms;
            SMVariant = smv;
            SMAverage = sma;

            LinesWidth = w;
            LinesHeight = h;

            RoundWidth = w;
            RoundHeight = h;

            RoundX = x;
            RoundY = y;
            RoundR = r;
            RoundX = x;

            FiguresWidth = w;
            FiguresHeight = h;
        }

    }
}
