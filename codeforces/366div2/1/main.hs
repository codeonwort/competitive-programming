import Data.Maybe
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

getDouble = read `fmap` getLine :: IO Double
getDoubles = map fromIntegral `fmap` getInts :: IO [Double]

love = "that I love "
hate = "that I hate "

main = do
	n <- getInt
	if n == 1 then putStrLn "I hate it"
	else putStrLn ("I hate " ++ build n ++ "it")

build 1 = ""
build n = build (n-1) ++ (if n `mod` 2 == 0 then love else hate)
