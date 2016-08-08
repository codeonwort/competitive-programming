import Data.List
import Data.Maybe
import Data.Char (ord)
import Data.Int
import Data.Bits

main = do
	n <- read `fmap` getLine :: IO Int
	flats <- getLine
	let poke = (map head . group . sort) flats
	let numPoke = length poke
	let goal = foldl1' (.|.) (map ord2 poke)
	let (curr, rest) = walk flats curr goal

ord2 :: Char -> Int64
ord2 ch
	| 'a' <= ch && ch <= 'z' = bit (ord ch - ord 'a')
	| 'A' <= ch && ch <= 'Z' = bit (26 + ord ch - ord 'A')

-- flats -> currSet -> currSteps -> goalSet -> (resultSet, numSteps, remainingFlats)
walk :: String -> Int64 -> Int -> Int64 -> (Int64, Int, String)
walk [] curr step goal = (curr, step, [])
walk (x:xs) curr step goal
	| 

minStep :: Int64 -> String -> Maybe Int
minStep goal flats = f flats 0 0 where
	f :: String -> Int64 -> Int -> Maybe Int
	f [] curr step
		| curr == goal = Just step
		| otherwise = Nothing
	f (x:xs) curr step
		| curr == goal = Just step
		| otherwise = f xs (curr .|. (ord2 x)) (step + 1)
