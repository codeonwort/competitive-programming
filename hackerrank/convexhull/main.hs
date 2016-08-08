import Control.Monad
import Data.List

-- ID:	Convex Hull
-- URL:	https://www.hackerrank.com/challenges/convex-hull-fp

getInt = read `fmap` getLine :: IO Int

main = do
	n <- getInt
	ps <- replicateM n $ do
		[x,y] <- (map read . words) `fmap` getLine :: IO [Double]
		return (x,y)
	print $ convexHull ps				-- vertices of the convex hull
	print $ perimeter $ convexHull ps	-- perimeter of the convex hull

-- perimeter of a polygon
perimeter (x0:xs) = f (x0:xs) 0 where
	f (p:[]) acc = acc + dist p x0
	f (p:q:xs) acc = f (q:xs) (acc + dist p q)

-- Euclidean distance
dist (x0,y0) (x1,y1) = sqrt $ (x0-x1)**2 + (y0-y1)**2

-- return the convex hull of a point set
convexHull (p:ps) = (convexify . merge . clockwise) (div4 p ps)

-- is (p0, p1, p2) concave? (clockwise)
concave (x0,y0) (x1,y1) (x2,y2) = (x2-x1)*(y1-y0) < (y2-y1)*(x1-x0)

-- is given polygon convex?
convex (x0:x1:xs) = f (x0:x1:xs) where
	f (p:q:[]) = not (concave p q x0) && not (concave q x0 x1)
	f (p:q:r:xs) = not (concave p q r) && f (q:r:xs)

-- eliminate unnecessary points
convexify xs
	| convex xs = xs
	| otherwise = convexify (reduce xs) where
		reduce (x0:xs0) = f (x0:xs0) [] where
			f (p:q:[]) ys
				| concave p q x0 = g p (reverse ys)
				| otherwise = g q (reverse (p:ys))
			f (p:q:r:xs) ys
				| concave p q r = f (p:r:xs) ys
				| otherwise = f (q:r:xs) (p:ys)
			g p (q:r:ys)
				| concave p q r = g p (r:ys)
				| otherwise = (q:r:ys) ++ [p]

-- merge the points which were divided into quadrants
merge (p0, ps) = (concat $ take n ps) ++ [p0] ++ (concat $ drop n ps) where
	n = case findIndex null ps of
			Nothing -> 0
			Just i -> i

-- sort points in clockwise order
clockwise (p@(x0,y0), ps) = (p, map (sortBy compareAngle) ps) where
	compareAngle (x1,y1) (x2,y2)
		| (y1-y0)/(x1-x0) == (y2-y0)/(x2-x0) = compare (dist (x0,y0) (x1,y1)) (dist (x0,y0) (x2,y2))
		| otherwise = compare ((y2-y0)*(x1-x0)) ((y1-y0)*(x2-x0)) 

-- given (x0,y0) as center, assign points into the quadrants
div4 (x0,y0) ps = f [] [] [] [] ps where
	f rt rb lb lt [] = ((x0,y0), [rt, rb, lb, lt])
	f rt rb lb lt ((x1,y1):ps)
		| (x1 > x0 && y1 > y0) || (y0 == y1 && x0 < x1) = f ((x1,y1):rt) rb lb lt ps -- top left
		| (x1 > x0 && y1 < y0) || (x0 == x1 && y0 > y1) = f rt ((x1,y1):rb) lb lt ps -- bottom left
		| (x1 < x0 && y1 < y0) || (y0 == y1 && x0 > x1) = f rt rb ((x1,y1):lb) lt ps -- bottom right
		| otherwise										= f rt rb lb ((x1,y1):lt) ps -- top right
