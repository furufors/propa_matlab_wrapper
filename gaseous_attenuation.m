function [gaseous_attenuation] = gaseous_attenuation(lat, lon, f, E)
    % lat = Latitude (°)
    % lon = Logitude (°)
    % hs  = Earth station altitude (km)
    % E   = Link elevation angle (rad)
    % f   = Link frequency (GHz)
    % to  = Tilt polarization angle (°)
    % D   = Earth station antenna diameter (m)
    % eta = Earth station antenna efficiency
    % p   = Percentage of the time (%)

    [status, command_output] = system(['gaseous_attenuation.exe'...
                                ' ' num2str(lat) ...
                                ' ' num2str(lon)...
                                ' ' num2str(f)...
                                ' ' num2str(E)]);
    gaseous_attenuation = str2double(command_output);
    return