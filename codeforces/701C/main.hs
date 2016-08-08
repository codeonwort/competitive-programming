import Data.List
import Data.Array
import Data.Maybe
import qualified Data.Map.Strict as M
import Debug.Trace

main = do
	n <- read `fmap` getLine :: IO Int
	flats <- getLine
	let flatAry = listArray (1, length flats) flats
	let numPoke = (length . group . sort) flats
	print $ solve numPoke flatAry

type Book = M.Map Char Int
type Solution = (Book, Int, Int) -- (currSet, beginIx, endIx)

solve numPoke flats = f (M.empty, 1, 1) 100000 where
	f :: Solution -> Int -> Int
	f curr best = case walk numPoke flats curr of
		Nothing -> best
		Just next -> f (removeHead next flats) (min best (cost next))
	cost (_, b, e) = e - b

removeHead (book, b, e) flats = (book', b+1, e) where
	x = flats ! b
	book' = if book M.! x == 1 then M.delete x book else M.adjust (\y->y-1) x book

walk :: Int -> Array Int Char -> Solution -> Maybe Solution
walk num flats (book, b, e) = f book e where
	(ary1, aryN) = bounds flats
	len = aryN - ary1 + 1
	f book e
		| e > len && M.size book >= num = Just (book, b, e)
		| e > len && M.size book < num = Nothing
		| M.size book == num = Just (book, b, e)
		| otherwise = f (M.insertWith (+) (flats ! e) 1 book) (e + 1)
