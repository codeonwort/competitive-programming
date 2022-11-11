-- ID:	703C (Chris and Road)
-- URL:	http://codeforces.com/contest/703/problem/C

-- Implemented the reference solution (https://codeforces.com/blog/entry/46434)
-- but the math is really dirty.

import Data.Maybe
import Data.List
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

getDouble = read `fmap` getLine :: IO Double
getDoubles = map fromIntegral `fmap` getInts :: IO [Double]

type Point = (Double, Double)
type Line = (Point, Point) -- ccw order
type Poly = [Line]

main = do
	-- input
	[n,w',v',u'] <- getInts
	let [w,v,u] = map fromIntegral [w',v',u'] :: [Double]
	ps <- replicateM n $ getDoubles >>= \[x,y] -> return (x,y)
	let bus = (head (reverse ps),head ps) : zip ps (tail ps)
	let walker = ((0,0),(2*w*(v/u),2*w))  :: Line
	-- solve
	let lb = 0.0
	let ub = fst $ maximumBy (\p q -> compare (fst p) (fst q)) ps -- not optimal but conservative
	let offX = binSearch lb ub bus walker
	if busHitTest bus walker
	then print $ (offX/v) + (w/u)
	else print $ (w/u)

-------------------------------------------------------------------------

binSearch :: Double -> Double -> Poly -> Line -> Double
binSearch lb ub bus walker =
	if (ub - lb) <= (0.5 * 1e-6)
	then lb
	else if busHitTest bus (shiftWalker walker mid)
		then binSearch mid ub bus walker
		else binSearch lb mid bus walker
			where mid = 0.5 * (lb + ub)

shiftWalker :: Line -> Double -> Line
shiftWalker ((x0,y0),(x1,y1)) offsetX = ((x0+offsetX,y0),(x1+offsetX,y1))

busHitTest :: Poly -> Line -> Bool
busHitTest edges walker = not (hits == [])
	where hits = filter (`lineHitTest` walker) edges

-- TODO: 
lineHitTest :: Line -> Line -> Bool
lineHitTest edge walker = intersects && notOnVertices && (m1 /= m2) where
	(m1,c1) = slopeForm edge
	(m2,c2) = slopeForm walker
	tx = if m2 == m1
		then (if c1 == c2 then (fst (midPoint walker)) else ((fst .fst) (shiftWalker walker (-100.0))))
		else (c1-c2)/(m2-m1)
	ty = m1 * tx + c1
	tp = (tx, ty)
	intersects = (contains walker tx ty) && (contains edge tx ty)
	notOnVertices = (notOnVertex edge tp) && (notOnVertex walker tp)
	notOnVertex ((x0,y0),(x1,y1)) (tx,ty) = not ((x0 == tx && y0 == ty) || (x1 == tx && y1 == ty))

midPoint ((x0,y0),(x1,y1)) = (0.5*(x0+x1),0.5*(y0+y1))

contains :: Line -> Double -> Double -> Bool
contains ((x1,y1),(x2,y2)) tx ty = minX <= tx && tx <= maxX && minY <= ty && ty <= maxY where
	minX = min x1 x2
	maxX = max x1 x2
	minY = min y1 y2
	maxY = max y1 y2

-- y = slope * x + offset
slopeForm :: Line -> (Double, Double) -- (slope, y-offset)
slopeForm ((x1,y1),(x2,y2)) = (slope, offset) where
	slope = (y2-y1) / (x2-x1)
	offset = -slope * x1 + y1

