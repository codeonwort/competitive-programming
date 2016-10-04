-- ID:  721A (One-dimensional Japanese Crossword)
-- URL: http://codeforces.com/problemset/problem/721/A

import Data.List
import Control.Monad

getInt = read `fmap` getLine :: IO Int

main = do
	n <- getInt
	s <- getLine
	let blocks = filter (\g -> head g == 'B') (group s)
	print $ length blocks
	forM_ blocks $ \block -> do
		putStr $ show (length block)
		putChar ' '
	putStrLn ""
