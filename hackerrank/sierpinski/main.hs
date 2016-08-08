import Control.Monad

-- ID:	Functions and Fractals: Sierpinski triangles
-- URL:	https://www.hackerrank.com/challenges/functions-and-fractals-sierpinski-triangles

type Triangle = ((Int,Int), (Int,Int), (Int,Int))

sierpinski n = f n [((32,1),(1,32),(63,32))] where
	f 0 vs = display 63 32 vs
	f n vs = f (n-1) $ (concat $ map divide vs)

divide ((x1,y1),(x2,y2),(x3,y3)) = [v1,v2,v3] where
	hx = (x1 + x2) `div` 2
	hx' = (x1 + x3) `div` 2
	hy = (y1 + y2) `div` 2
	v1 = ((x1,y1),(hx+1,hy),(hx',hy))
	v2 = ((hx,hy+1),(x2,y2),(x1-1,y2))
	v3 = ((hx'+1,hy+1),(x1+1,y3),(x3,y3))

display w h vs = newline 63 tbl where
	tbl = [if color x y == 1 then '1' else '_' | y <- [1..h], x <- [1..w]]
	color x y = length $ filter test vs where
		test ((x1,y1),(x2,y2),(x3,y3)) = y1 <= y && y <= y2 && x2 + (y2-y) <= x && x <= x3 - (y3-y)

newline _ [] = []
newline n ls = take n ls : newline n (drop n ls)

main = do
	n <- readLn :: IO Int
	let tri = sierpinski n
	forM_ tri $ \row -> putStrLn row
