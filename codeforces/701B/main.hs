import Data.List hiding (insert)
import Data.Int
import Data.IntSet hiding (map)

main = do
	[n,m] <- (map read . words) `fmap` getLine :: IO [Int]
	rocks <- (map (map read . words) . take m . lines) `fmap` getContents :: IO [[Int]]
	let n64 = fromIntegral n :: Int64
	solve rocks empty empty n64 n64

solve [] cols rows emptyCols emptyRows = return ()
solve ([x,y]:rocks) cols rows emptyCols emptyRows = do
	let col_already = member x cols
	let row_already = member y rows
	let emptyCols' = if col_already then emptyCols else emptyCols - 1
	let emptyRows' = if row_already then emptyRows else emptyRows - 1
	putStr $ show $ emptyCols' * emptyRows'
	putChar ' '
	let cols' = insert x cols
	let rows' = insert y rows
	solve rocks cols' rows' emptyCols' emptyRows'

{-
main = do
	[n,m] <- (map read . words) `fmap` getLine :: IO [Int]
	rocks <- (map (map read . words) . take m . lines) `fmap` getContents :: IO [[Int]]
	solve rocks n [] [] 0 0

solve [] _ _ _ _ _ = hFlush stdout
solve ([x,y]:rocks) n prevRs prevCs prevRsLen prevCsLen = do
	let r_already = y `elem` prevRs
	let c_already = x `elem` prevCs
	let (prevRs',prevRsLen') = if r_already then (prevRs,prevRsLen) else (y:prevRs,prevRsLen+1)
	let (prevCs',prevCsLen') = if c_already then (prevCs,prevCsLen) else (x:prevCs,prevCsLen+1)
	let w = fromIntegral n - fromIntegral (length prevRs') :: Int64
	let h = fromIntegral n - fromIntegral (length prevCs') :: Int64
--	putStr $ show $ (n - prevRsLen') * (n - prevCsLen')
	putStr $ show $ w * h
	putChar ' '
	solve rocks n prevRs' prevCs' prevRsLen' prevCsLen'
-}
