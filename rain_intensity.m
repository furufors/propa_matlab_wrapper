function [rain_intensity]=rain_intensity(lat,lon,p)
    % lat = Latitude (°)
    % lon = Logitude (°)
    % hs  = Earth station altitude (km)
    % E   = Link elevation angle (rad)
    % f   = Link frequency (GHz)
    % to  = Tilt polarization angle (°)
    % D   = Earth station antenna diameter (m)
    % eta = Earth station antenna efficiency
    % p   = Percentage of the time (%)
    
    [status, command_output] = system(['rain_intensity.exe'...
                                ' ' num2str(lat) ...
                                ' ' num2str(lon) ...
                                ' ' num2str(p)]);
        rain_intensity = str2double(command_output);