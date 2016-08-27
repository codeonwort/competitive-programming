import Data.Maybe
import Data.List
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import Debug.Trace

-- ID:	703C (Chris and Road)
-- URL:	http://codeforces.com/contest/703/problem/C

-- This is not an accepted code!

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

getDouble = read `fmap` getLine :: IO Double
getDoubles = map fromIntegral `fmap` getInts :: IO [Double]

type Point = (Double, Double)
type Line = (Point, Point, Int) -- ccw order, index
type Poly = [Line]

main = do
	[n,w',v',u'] <- getInts
	let [w,v,u] = map fromIntegral [w',v',u'] :: [Double]
	ps <- replicateM n $ getDoubles >>= \[x,y] -> return (x,y)
	let poly' = (head (reverse ps),head ps) : zip ps (tail ps)
	let poly = zipWith (\(p1,p2) i -> (p1,p2,i)) poly' [1..n-1]
	let walker = ((0,0),(w*(v/u),w), -1)  :: Line
	case polyHitTime poly walker of
		Nothing -> print (w/u)
		Just (time, edge) -> do
			let posEdges = takeWhile (`slowSlope` walker) $ dropWhile negativeSlope (drop (edgeIdx edge) (poly ++ poly))
			if posEdges == []
			then do
				let (_,(x0,y0),_) = edge
				let t0 = y0/u + (x0 - v*y0/u)/v
				let timeStraight = (w - y0) / u
				print $ t0 + timeStraight
			else do
				let ((x0,y0),_,_) = head posEdges
				let t0 = y0/u + (x0 - v*y0/u)/v
				let (timeOnEdges, heightOnEdges) = if posEdges == [] then (0,0) else foldl (followEdge v) (0,0) posEdges
				let timeStraight = (w - heightOnEdges - y0) / u
				print $ t0 + timeOnEdges + timeStraight
{-
			putStrLn $ "polyl:\t\t" ++ show poly
			putStrLn $ "Edge:\t\t" ++ show edge
			putStrLn $ "non-negs:\t\t" ++ show (dropWhile negativeSlope (drop (edgeIdx edge) (poly ++ poly)))
			putStrLn $ "posEdges:\t\t" ++ show posEdges
			putStrLn $ "t0:\t\t" ++ show t0
			putStrLn $ "t_edges:\t\t" ++ show timeOnEdges
			putStrLn $ "t_strai:\t\t" ++ show  timeStraight
-}

bottom :: Line -> Double
bottom ((_,y1),(_,y2),_) = min y1 y2

followEdge v (t,h) edge@((x1,y1),(x2,y2),_) = (t',h') where
	t' = t + dx/v
	h' = h + dy
	(slope,_) = slopeForm edge
	dx = x2 - x1
	dy = y2 - y1

edgeIdx (_,_,ix) = ix

slopeForm :: Line -> (Double, Double) -- (slope, y-offset)
slopeForm ((x1,y1),(x2,y2),_) = (slope, offset) where
	slope = (y2-y1) / (x2-x1)
	offset = -slope * x1 + y1

polyHitTime :: Poly -> Line -> Maybe (Double, Line)
polyHitTime edges walker
	| times == [] = Nothing
	| otherwise = Just $ minimumBy (\p q -> compare (fst p) (fst q)) times
	where times = map fromJust $ filter isJust (map (`lineHitTime` walker) edges)

lineHitTime :: Line -> Line -> Maybe (Double, Line)
lineHitTime edge walker = if contains walker tx && contains edge tx then Just (tx, edge) else Nothing where
	(m1,c1) = slopeForm edge
	(m2,c2) = slopeForm walker
	tx = (c1-c2)/(m2-m1)

contains :: Line -> Double -> Bool
contains ((x1,y1),(x2,y2),_) x = x1 <= x && x <= x2

insideLine :: Line -> Point -> Bool
insideLine ((x1,y1),(x2,y2),_) (x,y) = dx1*dy2 - dy1*dx2 < 0 where
	(dx1, dy1) = (x-x1, y-y1)
	(dx2, dy2) = (x2-x1, y2-y1)

slowSlope :: Line -> Line -> Bool
slowSlope edge walker = (not $ negativeSlope edge) && sEdge <= sWalker where
	(sEdge,_) = slopeForm edge
	(sWalker,_) = slopeForm walker

negativeSlope :: Line -> Bool
negativeSlope ((x1,y1),(x2,y2),_) = x2 /= x1 && (y2-y1)/(x2-x1) < 0

insidePoly :: Poly -> Point -> Bool
insidePoly poly pt = all (`insideLine` pt) poly
