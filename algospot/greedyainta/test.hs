import Control.Monad
import Control.Exception.Base
import Data.List

{-
main = do
	print 1
	print 1
	replicateM_ 100000 $ putStr (show 100000 ++ " ")
-}

{-
main = do
	str <- getContents
	let x = map (map read . words) (lines str) :: [[Int]]
	print x
-}

{-
main = do
	a <- getLine
	b <- getLine
	c <- getContents
	--c <- map read `fmap` words `fmap` getContents :: IO [Int]
	--print $ foldl' (+) 0 c
	print $ length c
	return ()
-}

main = do
	let x = replicate 100000 100000
	evaluate x
	let x' = reverse x
	evaluate x'
	print $ length x'
