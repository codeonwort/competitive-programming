-- ID  : 1569C (C. Jury Meeting)
-- URL : https://codeforces.com/contest/1569/problem/C

import Control.Monad

-- bytestring for fast IO
import Data.Maybe
import qualified Data.ByteString.Char8 as BS8
import qualified Data.ByteString as BS
getInt = parseInt `fmap` BS8.getLine :: IO Int
getInts = (map parseInt . BS8.words) `fmap` BS8.getLine :: IO [Int]
parseInt = fromIntegral . fst . fromJust . BS8.readInt

main = do
    t <- getInt
    replicateM_ t solve

solve = do
    n <- getInt
    as <- getInts
    -- todo

